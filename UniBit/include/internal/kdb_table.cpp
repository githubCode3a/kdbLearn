/**
 * @brief   C++ interface to read kdb+ table
 * 
 * @file    kdb_table.cpp
 * @author  Cody Feng <cody.feng"AT"outlook.com>
 * @date    2018-06-27
 */

#include "kdb_type.h"
#include "kdb_table.h"
#include<iostream>
namespace kdb {
    Table::Table(const Result &r) //: res_(r.res_),
                                   // n_rows_(kK(kK(res_->k)[1])[0]->n),
                                   // n_cols_(kK(res_->k)[0]->n) 
    {

        res_ = r.res_;                                
        kK(res_->k)[0];// no problem!!
        std::cout<<"[Table::table] yezheng!!!!!!\r\n";
        n_cols_ = kK(res_->k)[0]->n;// segmentation fault!!

        std::cout<<"[Table::table] kK(res_->k)[0]->n; "<< n_cols_ << " yezheng!!!!!!\r\n";
        n_rows_ = kK(kK(res_->k)[1])[0]->n; // segmentation fault!!
        std::cout<<"[Table::table] kK(kK(res_->k)[1])[0]->n;"<<n_rows_ <<" yezheng!!!!!!\r\n";
        
        
        
        if (res_) {
            r1(res_);
        }
    }

    Table::~Table() {
        if (res_) {
            r0(res_);
            res_ = nullptr;
        }
    }

    Vector<Type::Symbol> Table::get_header() {
        return Result(kK(res_->k)[0]).get_vector<Type::Symbol>();
    }

}
