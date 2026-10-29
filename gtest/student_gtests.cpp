#include <gtest/gtest.h>
#include <string.h>

#include <algorithm>

#include "string.hpp"
#include "alloc.hpp"

TEST(StringFunction, strlen) {
    EXPECT_EQ(String::strlen(""), 0);
    EXPECT_EQ(String::strlen("a"), 1);
    EXPECT_EQ(String::strlen("hey there"), 9);
    EXPECT_EQ(String::strlen("a!b?c"), 5);
}

TEST(StringFunction, strcpy) {
    char copy[20];
    EXPECT_EQ(String::strcpy(copy, "pizza"), copy);
    EXPECT_STREQ(copy, "pizza");

    String::strcpy(copy, "x");
    EXPECT_STREQ(copy, "x");

    String::strcpy(copy, "hi, you!");
    EXPECT_STREQ(copy, "hi, you!");

    String::strcpy(copy, "");
    EXPECT_STREQ(copy, "");
}

TEST(StringFunction, strncpy) {
    char copy[20];
    EXPECT_EQ(String::strncpy(copy, "window", 3), copy);
    EXPECT_STREQ(copy, "win");

    String::strncpy(copy, "cup", 10);
    EXPECT_STREQ(copy, "cup");

    String::strncpy(copy, "cup", 3);
    EXPECT_STREQ(copy, "cup");

    String::strncpy(copy, "a.b.c", 2);
    EXPECT_STREQ(copy, "a.");

    String::strncpy(copy, "cup", 0);
    EXPECT_STREQ(copy, "");

    String::strncpy(copy, "", 4);
    EXPECT_STREQ(copy, "");
}

TEST(StringFunction, strcat) {
    char word[30] = "rain";
    EXPECT_EQ(String::strcat(word, "bow"), word);
    EXPECT_STREQ(word, "rainbow");

    String::strcat(word, "");
    EXPECT_STREQ(word, "rainbow");

    String::strcat(word, "!");
    EXPECT_STREQ(word, "rainbow!");

    char blank[10] = "";
    String::strcat(blank, "z");
    EXPECT_STREQ(blank, "z");
}

TEST(StringFunction, strncat) {
    char word[30] = "sun";
    EXPECT_EQ(String::strncat(word, "flowers", 6), word);
    EXPECT_STREQ(word, "sunflower");

    String::strncat(word, "?!", 1);
    EXPECT_STREQ(word, "sunflower?");

    String::strncat(word, "abc", 0);
    EXPECT_STREQ(word, "sunflower?");
}

TEST(StringFunction, strcmp) {
    EXPECT_EQ(String::strcmp("moon", "moon"), 0);
    EXPECT_LT(String::strcmp("bat", "cat"), 0);
    EXPECT_GT(String::strcmp("cat", "bat"), 0);
    EXPECT_LT(String::strcmp("car", "card"), 0);
    EXPECT_GT(String::strcmp("card", "car"), 0);
    EXPECT_EQ(String::strcmp("", ""), 0);
    EXPECT_LT(String::strcmp("", "!"), 0);
}

TEST(StringFunction, strncmp) {
    EXPECT_EQ(String::strncmp("table", "tablet", 5), 0);
    EXPECT_LT(String::strncmp("table", "tablet", 6), 0);
    EXPECT_EQ(String::strncmp("red", "blue", 0), 0);
    EXPECT_EQ(String::strncmp("same", "same", 50), 0);
    EXPECT_LT(String::strncmp("hi", "hit", 3), 0);
}

TEST(StringFunction, reverse_cpy) {
    char flipped[20];
    String::reverse_cpy(flipped, "stressed");
    EXPECT_STREQ(flipped, "desserts");

    String::reverse_cpy(flipped, "ok");
    EXPECT_STREQ(flipped, "ko");

    String::reverse_cpy(flipped, "!");
    EXPECT_STREQ(flipped, "!");

    String::reverse_cpy(flipped, "");
    EXPECT_STREQ(flipped, "");
}

TEST(StringFunction, strchr) {
    const char * word = "balloon";
    EXPECT_EQ(String::strchr(word, 'b'), word);
    EXPECT_EQ(String::strchr(word, 'l'), word + 2);
    EXPECT_EQ(String::strchr(word, 'n'), word + 6);
    EXPECT_EQ(String::strchr(word, 'q'), nullptr);
    EXPECT_EQ(String::strchr(word, '\0'), word + 7);
    EXPECT_EQ(String::strchr("", 'x'), nullptr);
}

TEST(StringFunction, strstr) {
    const char * text = "mississippi";
    EXPECT_EQ(String::strstr(text, "i"), text + 1);
    EXPECT_EQ(String::strstr(text, "ssip"), text + 5);
    EXPECT_EQ(String::strstr(text, "mississippi"), text);
    EXPECT_EQ(String::strstr(text, ""), text);
    EXPECT_EQ(String::strstr(text, "xyz"), nullptr);
    EXPECT_EQ(String::strstr(text, "mississippi river"), nullptr);
}
