#include <cassert>
#include <exception>
#include <stdexcept>
#include <cstring>
#include <utility>

#include <gtest/gtest.h>

namespace pn {
    template<typename T>
    class basic_string {
    private:
        size_t _len = 0;
        T* _ptr = nullptr;

        void deep_copy(const basic_string &other) {
            _len = other._len;
            _ptr = new T[_len];
            memcpy(_ptr, other._ptr, other._len);
        }

        void free() {
            delete []_ptr;
            _len = 0;
        }

    public:
        const T *c_str() const {
            return _ptr;
        }

        size_t size() const {
            return _len;
        }

        basic_string() = default;
        ~basic_string() {
            free();
        }

        explicit basic_string(const char *data) {
            if (nullptr == data) {
                throw std::runtime_error("data is null");
            }
            _len = strlen(data);
            _ptr = new T[_len];
            memcpy(_ptr, data, _len);
        }

        basic_string(const basic_string& other) {
            deep_copy(other);
        }

        basic_string(basic_string&& other)  noexcept :
                _len(std::exchange(other._len, 0)),
                _ptr(std::exchange(other._ptr, nullptr)) {
        }

        basic_string& operator = (const basic_string& other) {
            if (this == &other) {
                return *this;
            }
            deep_copy(other);
            return *this;
        }

    };

    using string = pn::basic_string<char>;
}

class TestString : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestString, testConstructor) {
    pn::string s;
    EXPECT_EQ(s.size(), 0);
    EXPECT_EQ(s.c_str(),nullptr);
}

TEST_F(TestString, testConstructorWithArgs) {
    EXPECT_ANY_THROW(pn::string s(nullptr));

    pn::string s("Hello World !!!");
    EXPECT_EQ(s.size(), strlen(s.c_str()));
    EXPECT_STREQ(s.c_str(),"Hello World !!!");
}

TEST_F(TestString, testCopy) {
    pn::string s("Hello World !!!");
    pn::string s1(s);
    EXPECT_EQ(s1.size(), s.size());
    EXPECT_STREQ(s1.c_str(), s.c_str());
}

TEST_F(TestString, moveConstructor) {
    pn::string s("Hello World !!!");
    pn::string s1(std::move(s));
    EXPECT_EQ(s.size(), 0);
    EXPECT_EQ(s.c_str(), nullptr);

    EXPECT_EQ(s1.size(), strlen("Hello World !!!"));
    EXPECT_STREQ(s1.c_str(), "Hello World !!!");
}

TEST_F(TestString, assignmentCopy) {
    pn::string s("Hello World !!!");
    pn::string s1 = s;
    EXPECT_EQ(s1.size(), s.size());
    EXPECT_STREQ(s1.c_str(), s.c_str());
}

TEST_F(TestString, assignmentMove) {
    pn::string s("Hello World !!!");
    size_t len = strlen(s.c_str());
    pn::string s1 = std::move(s);
    EXPECT_EQ(s.size(), 0);
    EXPECT_EQ(s.c_str(), nullptr);

    EXPECT_EQ(s1.size(), len);
    EXPECT_STREQ(s1.c_str(),"Hello World !!!");
}
