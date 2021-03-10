/**
 * An example of how to write unit tests.
 * Use this as a basis to build a more complete Test.cpp file.
 * 
 * IMPORTANT: Please write more tests - the tests here are only for example and are not complete.
 *
 * AUTHORS: <Please write your names here>
 * 
 * Date: 2021-02
 */

#include "doctest.h"
#include "snowman.hpp"
#include <math.h>

#include <string>
#include <algorithm>
#include <sstream>

#define MAX_OPTIONS_PER_ITEM 4
#define NUM_ITEMS 8
#define DEFAULT_FORMAT 11111111

using namespace ariel;

// Holds visual object that span across two lines
struct UpperLowerObject {
    std::string upper;
    std::string lower;

    UpperLowerObject(std::string u, std::string l) : upper(u), lower(l) {};
};

// Single line objects
struct SingleObject {
    std::string item;

    SingleObject(std::string i) : item(i) {};
};


std::string create_snowman(const UpperLowerObject &hat,
                           const UpperLowerObject &right_hand,
                           const UpperLowerObject &left_hand,
                           const SingleObject &nose,
                           const SingleObject &right_eye,
                           const SingleObject &left_eye,
                           const SingleObject &torso,
                           const SingleObject &base) {

    std::stringstream fmt;

    fmt << " " << hat.upper << "\n"
        << " " << hat.lower << "\n"
        << left_hand.upper << "(" << left_eye.item << nose.item << right_eye.item << ")" << right_hand.upper << "\n"
        << left_hand.lower << "(" << torso.item << ")" << right_hand.lower << "\n"
        << " " << "(" << base.item << ")" << " ";

    return fmt.str();
}

unsigned int create_snowman_id(unsigned int h_hat_idx,
                               unsigned int n_nose_idx,
                               unsigned int l_left_eye_idx,
                               unsigned int r_right_eye_idx,
                               unsigned int x_left_arm_idx,
                               unsigned int y_right_arm_idx,
                               unsigned int t_torso_idx,
                               unsigned int b_base_idx) {

    return 10 ^ 7 * h_hat_idx +
                10 ^ 6 * n_nose_idx +
                     10 ^ 5 * l_left_eye_idx +
                          10 ^ 4 * r_right_eye_idx +
                               10 ^ 3 + x_left_arm_idx +
                                    10 ^ 2 + y_right_arm_idx +
                                         10 ^ 1 + t_torso_idx
                                              + b_base_idx;
}

TEST_CASE ("Test bad values") {
    CHECK_THROWS(snowman(DEFAULT_FORMAT - 1));
    CHECK_THROWS(snowman(DEFAULT_FORMAT * MAX_OPTIONS_PER_ITEM + 1));
    CHECK_THROWS(snowman(DEFAULT_FORMAT * -1));
    CHECK_THROWS(snowman(0));
}

TEST_CASE ("Test all possible values and ranges obj by obj") {

    unsigned int snowman_id = 0;

    for (int power = 0; power < NUM_ITEMS; ++power) {
        //Check min boundary (0)
        snowman_id = DEFAULT_FORMAT - pow(10, power);
        CHECK_THROWS(snowman(snowman_id));

        // Check all good options for items one by one
        for (int i = 1; i <= MAX_OPTIONS_PER_ITEM;
             ++i) {
            snowman_id = DEFAULT_FORMAT - pow(10, power);
            snowman_id += pow(10, power) * i;
                    CHECK(snowman(snowman_id) != "");
        }

        //Check max boundary (4 + 1)
        snowman_id = DEFAULT_FORMAT - pow(10, power);
        snowman_id += pow(10, power) * (MAX_OPTIONS_PER_ITEM
                                        + 1);
        CHECK_THROWS(snowman(snowman_id));
    }
}


// Can also be implemented using paramitization features of doctest
TEST_CASE ("Test all possible snowman permutations") {
    std::vector<std::tuple<unsigned int, UpperLowerObject>> hats{{1, {"     ",
                                                                             "_===_"}},
                                                                 {2, {" ___ ",
                                                                             "....."}},
                                                                 {3, {"  _  ",
                                                                             " /_\\ "}},
                                                                 {4, {" ___ ",
                                                                             "(_*_)"}}
    };


    std::vector<std::tuple<unsigned int, UpperLowerObject>> right_hands{{1, {" ",
                                                                                    ">"}},
                                                                        {2, {"/",
                                                                                    " "}},
                                                                        {3, {" ",
                                                                                    "\\"}},
                                                                        {4, {" ",
                                                                                    " "}}
    };

    std::vector<std::tuple<unsigned int, UpperLowerObject>> left_hands{{1, {" ",
                                                                                   "<"}},
                                                                       {2, {"\\",
                                                                                   " "}},
                                                                       {3, {" ",
                                                                                   "/"}},
                                                                       {4, {" ",
                                                                                   " "}}
    };

    std::vector<std::tuple<unsigned int, SingleObject>> noses{{1, {","}},
                                                              {2, {"."}},
                                                              {3, {"_"}},
                                                              {4, {" "}}};

    std::vector<std::tuple<unsigned int, SingleObject>> eyes{{1, {"."}},
                                                             {2, {"o"}},
                                                             {3, {"O"}},
                                                             {4, {"-"}}};

    std::vector<std::tuple<unsigned int, SingleObject>> torsos{{1, {":::"}},
                                                               {2, {"] ["}},
                                                               {3, {"> <"}},
                                                               {4, {"   "}}};


    std::vector<std::tuple<unsigned int, SingleObject>> bases{{1, {" : "}},
                                                              {2, {"\" \""}},
                                                              {3, {"___"}},
                                                              {4, {"   "}}};



    // Ew, maybe can be made prettier with SUB_CASE
    for (auto &hat : hats) {
        for (auto &left_hand : left_hands) {
            for (auto &right_hand : right_hands) {
                for (auto &nose : noses) {
                    for (auto &left_eye : eyes) {
                        for (auto &right_eye : eyes) {
                            for (auto &torso : torsos) {
                                for (auto &base : bases) {

                                    unsigned int hat_idx = std::get<unsigned int>(hat);
                                    UpperLowerObject hat_obj = std::get<UpperLowerObject>(hat);

                                    unsigned int left_hand_idx = std::get<unsigned int>(left_hand);
                                    UpperLowerObject left_hand_obj = std::get<UpperLowerObject>(left_hand);

                                    unsigned int right_hand_idx = std::get<unsigned int>(right_hand);
                                    UpperLowerObject right_hand_obj = std::get<UpperLowerObject>(right_hand);

                                    unsigned int nose_idx = std::get<unsigned int>(nose);
                                    SingleObject nose_obj = std::get<SingleObject>(nose);

                                    unsigned int left_eye_idx = std::get<unsigned int>(left_eye);
                                    SingleObject left_eye_obj = std::get<SingleObject>(left_eye);

                                    unsigned int right_eye_idx = std::get<unsigned int>(right_eye);
                                    SingleObject right_eye_obj = std::get<SingleObject>(right_eye);

                                    unsigned int torso_idx = std::get<unsigned int>(torso);
                                    SingleObject torso_obj = std::get<SingleObject>(torso);

                                    unsigned int base_idx = std::get<unsigned int>(base);
                                    SingleObject base_obj = std::get<SingleObject>(base);

                                    std::string expected_snowman = create_snowman(hat_obj,
                                                                                  right_hand_obj,
                                                                                  left_hand_obj,
                                                                                  nose_obj,
                                                                                  right_eye_obj,
                                                                                  left_eye_obj,
                                                                                  torso_obj,
                                                                                  base_obj);

                                    unsigned snowman_id = create_snowman_id(hat_idx,
                                                                            nose_idx,
                                                                            left_eye_idx,
                                                                            right_eye_idx,
                                                                            left_hand_idx,
                                                                            right_hand_idx,
                                                                            torso_idx,
                                                                            base_idx);

                                    CHECK(snowman(snowman_id) == expected_snowman);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

}
