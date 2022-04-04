#pragma once

#include <gui/mainwindow.h>

#include <QApplication>
#include <iostream>

#include <generic/types.h>
#include <generic/vec_ops.h>
#include <generic/serialize.h>
#include <generic/test_data.h>

#include <ranges>

#include <database/text.h>

#include <generic/print.h>



int main(int argc, char *argv[])
{
//    TestData test_data;
//    print_table plsment(test_data.texts_.txt_);

    vector<uint8> vec1{3, 0, 1, 2, 6, 5, 2, 3, 0};
    vector<uint8> vec11{3, 0, 1, 2, 6, 5, 2, 3, 0};
    vector<string> vec2{"all", "sort", "me", "together", "cunts", "other",
                        "with", "the", "Please"};

    sort_vecs(vec1, vec11, vec2);
    new print_table(vec1, vec11, vec2);

//    vector<uint8> vec2{0, 0, 1, 2, 2, 3, 3, 5, 6};

//    print_table vec1print(vec1);
////    sort_vecs(vec1);
//    print_table vec2print(vec2);

//    auto index_diff = map_vector_index_dif(vec1, vec2);
//    print_table idx_diff_print(index_diff.old_idx, index_diff.new_idx);
//    sort_vec_with_idx_diff(index_diff, vec1);
//    print_table vec1printafter(vec1);

//    print_table diff(index_diff.old_idx, index_diff.new_idx);

//    print_table pr3(vec1, vec2);
//    print_table diff(index_diff.old_idx, index_diff.new_idx);

//    QApplication a(argc, argv);
//    MainWindow w(nullptr, &test_data.texts_);
//    w.show();
//    return a.exec();
}
