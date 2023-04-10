#include <cstring>
#include <iostream>

class String {
  public:
    String() = default;
    String(const char *string) {
        printf("Created!\n");
        m_Size = strlen(string);
        m_Data = new char[m_Size];
        memcpy(m_Data, string, m_Size);
    }

    String(const String &other) {
        printf("Copied!\n");
        m_Size = other.m_Size;
        m_Data = new char[m_Size];
        memcpy(m_Data, other.m_Data, m_Size);
    }

    String(String &&other) {
        printf("Moved!\n");
        m_Size = other.m_Size;
        m_Data = other.m_Data;
        other.m_Data = nullptr;
        other.m_Size = 0;
    }

    ~String() {
        printf("Destroyed!\n");
        delete[] m_Data;
    }

    String &operator=(String &&other) {
        printf("Moved\n");
        if (this != &other) {
            delete[] m_Data;

            m_Size = other.m_Size;
            m_Data = other.m_Data;

            other.m_Data = nullptr;
            other.m_Size = 0;
        }
        return *this;
    }

    void Print() {
        for (uint32_t i = 0; i < m_Size; ++i)
            printf("%c", m_Data[i]);

        printf("\n");
    }

  private:
    char *m_Data;
    uint32_t m_Size;
};

class Entity {
  public:
    // Entity(const String& name)
    //     : m_Name(name) {}

    Entity(String &&name) : m_Name(std::move(name)) {}

    void PrintName() { m_Name.Print(); }

  private:
    String m_Name;
};

int main(int argc, const char *argv[]) {
    // Entity entity(String("Cherno"));
    // entity.PrintName();

    String apple = "apple";
    String orange = "orange";

    printf("apple: ");
    apple.Print();
    printf("orange: ");
    orange.Print();
    apple = std::move(orange);
    printf("apple: ");
    apple.Print();
    printf("orange: ");
    orange.Print();
    return 0;
}