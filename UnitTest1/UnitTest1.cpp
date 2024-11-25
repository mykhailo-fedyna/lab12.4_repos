#include "pch.h"
#include "CppUnitTest.h"
#include "../lab12.4.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(UnitTest1)
    {
    public:
        // Тест для додавання людини
        TEST_METHOD(TestSortByZodiac)
        {
            Zodiac people[3] = {
                { "Іваненко", "Олена", "Овен", {15, 4, 1990} },
                { "Петренко", "Сергій", "Телець", {20, 5, 1985} },
                { "Сидоров", "Анатолій", "Риби", {5, 3, 1992} }
            };

            int size = 3;

            sortByZodiac(people, size); // Сортуємо

            Assert::AreEqual(people[0].zodiac_sign.c_str(), "Овен");
            Assert::AreEqual(people[1].zodiac_sign.c_str(), "Риби");
            Assert::AreEqual(people[2].zodiac_sign.c_str(), "Телець");
        }



    };
};

