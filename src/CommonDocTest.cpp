#include<iostream>
#include<typeinfo>
#include<string>
#include<memory>
#include<vector>
#include<map>
#include<unordered_map>
#include<chrono>


enum FieldValueCase {
    kIValue = 1,  // int32
    kI64Value = 2,  // int64
    kFValue = 3,  // float
    kSValue = 4,  // string
    kIValues = 5,  // int32 list
    kI64Values = 6,  // int64 list
    kFValues = 7,  // float list
    kSValues = 8,  // string list
    kIToFMap = 9,  // <int32, float> map
    VALUE_NOT_SET = 0,
};

class BasicField {
public:
    virtual ~BasicField() {}
};

template <typename T>
class Field : public BasicField {
public:
    T field;
};

class OriginTempalte {
public:
    template <typename FieldType>
    const FieldType& getDocField() const {
        return std::dynamic_pointer_cast< Field<FieldType> >(field_)->field;
    }
    std::shared_ptr<BasicField> field_;
};


class CommonDocField {
public:
    using IVec = std::vector<int>;
    using I64Vec = std::vector<int64_t>;
    using FVec = std::vector<float>;
    using SVec = std::vector<std::string>;
    using IToFMap = std::unordered_map<int, float>;
public:
    CommonDocField() noexcept : type_(FieldValueCase::VALUE_NOT_SET){}
    explicit CommonDocField(FieldValueCase type) noexcept {
        alloc_by_type(type);
    }

    CommonDocField(const CommonDocField& rhs) noexcept {
        copy_filed(rhs);
    }
    CommonDocField& operator= (const CommonDocField& rhs) noexcept {
        if(this != &rhs) {
            copy_filed(rhs);
        }
        return *this;
    }

    CommonDocField(CommonDocField&& rhs) noexcept {
        move_filed(std::move(rhs));
    }
    CommonDocField& operator= (CommonDocField&& rhs) noexcept {
        if(this != &rhs) {
            move_filed(std::move(rhs));
        }
        return *this;
    }

    ~CommonDocField() { clear(); }

#define COMMONDOC_SET_OPER(value_type, inner_type, value_name) \
        CommonDocField& operator=(const value_type& val) { \
          realloc_by_type(inner_type); \
          value_name = val; \
          return *this; \
        }

    COMMONDOC_SET_OPER(int, FieldValueCase::kIValue, i_value)
    COMMONDOC_SET_OPER(int64_t, FieldValueCase::kI64Value, i64_value)
    COMMONDOC_SET_OPER(float, FieldValueCase::kFValue, f_value)
    COMMONDOC_SET_OPER(std::string, FieldValueCase::kSValue, s_value)
    COMMONDOC_SET_OPER(IVec, FieldValueCase::kIValues, i_values)
    COMMONDOC_SET_OPER(I64Vec, FieldValueCase::kI64Values, i64_values)
    COMMONDOC_SET_OPER(FVec, FieldValueCase::kFValues, f_values)
    COMMONDOC_SET_OPER(SVec, FieldValueCase::kSValues, s_values)
    COMMONDOC_SET_OPER(IToFMap, FieldValueCase::kIToFMap, itof_map_values)

#define COMMONDOC_GET_OPER(value_type, value_name) \
        operator const value_type&() const { return value_name; } \
        operator value_type() { return value_name; }

    COMMONDOC_GET_OPER(int, i_value)
    COMMONDOC_GET_OPER(int64_t, i64_value)
    COMMONDOC_GET_OPER(float, f_value)
    COMMONDOC_GET_OPER(std::string, s_value)
    COMMONDOC_GET_OPER(IVec, i_values)
    COMMONDOC_GET_OPER(I64Vec, i64_values)
    COMMONDOC_GET_OPER(FVec, f_values)
    COMMONDOC_GET_OPER(SVec, s_values)
    COMMONDOC_GET_OPER(IToFMap, itof_map_values)

private:
    void realloc_by_type(FieldValueCase type) {
        if(type == type_) {
            return;
        }
        clear();
        alloc_by_type(type);
    }
    void clear() {
        switch(type_) {
            case FieldValueCase::kSValue:
                s_value.~basic_string();
                break;
            case FieldValueCase::kIValues:
                i_values.~vector();
                break;
            case FieldValueCase::kI64Values:
                i64_values.~vector();
                break;
            case FieldValueCase::kFValues:
                f_values.~vector();
                break;
            case FieldValueCase::kSValues:
                s_values.~vector();
                break;
            case FieldValueCase::kIToFMap:
                itof_map_values.~unordered_map();
                break;
            default:
                break;
        }
    }

    void alloc_by_type(FieldValueCase type) {
        type_ = type;
        switch(type) {
            case FieldValueCase::kSValue:
                new (&s_value) std::string();
                break;
            case FieldValueCase::kIValues:
                new (&i_values) IVec;
                break;
            case FieldValueCase::kI64Values:
                new (&i64_values) I64Vec;
                break;
            case FieldValueCase::kFValues:
                new (&f_values) FVec;
                break;
            case FieldValueCase::kSValues:
                new (&s_values) SVec;
                break;
            case FieldValueCase::kIToFMap:
                new (&itof_map_values) IToFMap;
                break;
            default:
                break;
        }
    }

    void copy_filed(const CommonDocField& rhs) {
        type_ = rhs.type_;
        switch(type_) {
            case FieldValueCase::kIValue:
                i_value = rhs.i_value;
                break;
            case FieldValueCase::kI64Value:
                i64_value = rhs.i64_value;
                break;
            case FieldValueCase::kFValue:
                f_value = rhs.f_value;
                break;
            case FieldValueCase::kSValue:
                new (&s_value) std::string(rhs.s_value);
                break;
            case FieldValueCase::kIValues:
                new (&i_values) IVec(i_values);
                break;
            case FieldValueCase::kI64Values:
                new (&i64_values) I64Vec(rhs.i64_values);
                break;
            case FieldValueCase::kFValues:
                new (&f_values) FVec(rhs.f_values);
                break;
            case FieldValueCase::kSValues:
                new (&s_values) SVec(rhs.s_values);
                break;
            case FieldValueCase::kIToFMap:
                new (&itof_map_values) IToFMap(rhs.itof_map_values);
                break;
            default:
                break;
        }
    }
    void move_filed(CommonDocField&& rhs) {
        type_ = rhs.type_;
        switch(type_) {
            case FieldValueCase::kIValue:
                i_value = rhs.i_value;
                break;
            case FieldValueCase::kI64Value:
                i64_value = rhs.i64_value;
                break;
            case FieldValueCase::kFValue:
                f_value = rhs.f_value;
                break;
            case FieldValueCase::kSValue:
                new (&s_value) std::string(std::move(rhs.s_value));
                break;
            case FieldValueCase::kIValues:
                new (&i_values) IVec(std::move(rhs.i_values));
                break;
            case FieldValueCase::kI64Values:
                new (&i64_values) I64Vec(std::move(rhs.i64_values));
                break;
            case FieldValueCase::kFValues:
                new (&f_values) FVec(std::move(rhs.f_values));
                break;
            case FieldValueCase::kSValues:
                new (&s_values) SVec(std::move(rhs.s_values));
                break;
            case FieldValueCase::kIToFMap:
                new (&itof_map_values) IToFMap(std::move(rhs.itof_map_values));
                break;
            default:
                break;
        }
        rhs.type_ = FieldValueCase::VALUE_NOT_SET;
    }
private:
    FieldValueCase type_;
private:
    union {
        int32_t i_value;
        int64_t i64_value;
        float f_value;
        std::string s_value;
        IVec i_values;
        I64Vec i64_values;
        FVec f_values;
        SVec s_values;
        IToFMap itof_map_values;
    };
};



class TestUnion {
public:
    template <typename FieldType>
    const FieldType& getDocField() const {
        return field_;
    }
    CommonDocField field_;
};

class TestTemplate {
public:
    template <typename FieldType>
    const FieldType& getDocField() const {
        return ((Field<FieldType>*)field_)->field;
    }
    BasicField* field_;
};


class TimeKeeper {
public:
    TimeKeeper(std::string tag) : tag_(tag)
            ,begin_ ( std::chrono::high_resolution_clock::now() ) {}

    ~TimeKeeper() {
        auto end = std::chrono::high_resolution_clock::now();
        std::cout << "    " << tag_.c_str() << ":"
                  << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin_).count()
                  << std::endl;
    }
private:
    std::string tag_;
    std::chrono::time_point<std::chrono::high_resolution_clock> begin_;
};

const int counter = 200000;

template<typename T>
void fun(T val) {
    // std::cout << val << std::endl;
}

void fun(std::string str) {

}

template <typename T>
void TestCase(std::string test_name, T value)
{
    std::cout <<  test_name.c_str() << std::endl;

    OriginTempalte origin;
    origin.field_ = std::make_shared<Field<T>>();
    std::dynamic_pointer_cast< Field<T> >(origin.field_)->field = value;

    TestUnion my_union;
    my_union.field_ = value;

    TestTemplate my_template;
    my_template.field_ = new Field<T>();
    (( Field<T> *)(my_template.field_))->field = value;


    {
        TimeKeeper keeper("orgin");
        for (int i = 0; i < counter; i++)
        {
            auto num = origin.getDocField<T>();
            fun(num);
        }
    }

    {
        TimeKeeper keeper("union");
        for (int i = 0; i < counter; i++)
        {
            auto num = my_union.getDocField<T>();
            fun(num);
        }
    }

    {
        TimeKeeper keeper("template");
        for (int i = 0; i < counter; i++)
        {
            auto num = my_template.getDocField<T>();
            fun(num);
        }
    }

}

int main()
{
    TestCase<int>("test_int",5);
    TestCase<float>("test_float",1.0f);
    TestCase<std::string>("test_string","123");
    TestCase<std::vector<int> >("int_vec", {1,2,3});
    TestCase<std::vector<float> >("float_vec", {1,2,3});
    TestCase<std::vector<std::string> >("string_vec", {"1","2","3"});
    using IToFMap = std::unordered_map<int, float>;
    TestCase<IToFMap>("unorderd_map", {{1,0.1f}, {2,0.2f}, {3,0.3f}} );
    return 0;
}