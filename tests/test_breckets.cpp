#include <gtest/gtest.h>
#include "check_breckets.hpp"

TEST(BracketsTest, ValidSequences) {
    EXPECT_TRUE(check_breckets("{(())()[()()]}"));
    EXPECT_TRUE(check_breckets("()"));
    EXPECT_TRUE(check_breckets("[{}]"));
    EXPECT_TRUE(check_breckets(""));
}

TEST(BracketsTest, InvalidSequences) {
    EXPECT_FALSE(check_breckets("{("));
    EXPECT_FALSE(check_breckets("}"));
    EXPECT_FALSE(check_breckets("[(])"));
    EXPECT_FALSE(check_breckets("({)}"));
}

TEST(BracketsTest, WithText) {
    EXPECT_TRUE(check_breckets("int main() { return 0; }"));
    EXPECT_FALSE(check_breckets("int main() { return 0;"));
}