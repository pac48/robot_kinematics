#pragma once

#include "forward_kinematics.hpp"

namespace fast_fk::internal {
  enum OP {
    ROT,
    TRANS
  };

  // row major
  constexpr std::array<double, 10 * 9> R_all = {1.0, 0.0, 0.0,
                                                0.0, 1.0, 0.0,
                                                0.0, 0.0, 1.0,
                                                1.0, 0.0, 0.0,
                                                0.0, 1.0, 0.0,
                                                0.0, 0.0, 1.0,
                                                1.0, 0.0, 0.0,
                                                0.0, 1.0, 0.0,
                                                0.0, 0.0, 1.0,
                                                1.0, 0.0, 0.0,
                                                0.0, 1.0, 0.0,
                                                0.0, 0.0, 1.0,
                                                1.0, 0.0, 0.0,
                                                0.0, 1.0, 0.0,
                                                0.0, 0.0, 1.0,
                                                1.0, 0.0, 0.0,
                                                0.0, 1.0, 0.0,
                                                0.0, 0.0, 1.0,
                                                1.0, 0.0, 0.0,
                                                0.0, 1.0, 0.0,
                                                0.0, 0.0, 1.0,
                                                1.0, 0.0, 0.0,
                                                0.0, 1.0, 0.0,
                                                0.0, 0.0, 1.0,
                                                1.0, 0.0, 0.0,
                                                0.0, 1.0, 0.0,
                                                0.0, 0.0, 1.0,
                                                1.0, 0.0, 0.0,
                                                0.0, 1.0, 0.0,
                                                0.0, 0.0, 1.0,
  };


  constexpr std::array<double, 10 * 3> offset_all = {-0.05, 0.0, 0.739675,
                                                     0.0, 0.188, 0.0,
                                                     0.1, 0.0, 0.0,
                                                     0.0, 0.0, 0.0,
                                                     0.4, 0.0, 0.0,
                                                     0.0, 0.0, 0.0,
                                                     0.321, 0.0, 0.0,
                                                     0.0, 0.0, 0.0,
                                                     0.07691, -0.01, 0.0,
                                                     0.09137, -0.00495, 0.0,
  };


  template<OP ...T>
  inline void
  forward_kinematics_internal_ptr(double *input_data) {
    // sin(t) cos(t)  R11, R12, R13... px py pz
    constexpr int size = 2 + 3 + 9 + 3; // 17


    {
      constexpr std::size_t ind = 0;
      // row major
      const double &R11_fixed = R_all[ind * 9 + 0];
      const double &R21_fixed = R_all[ind * 9 + 1];
      const double &R31_fixed = R_all[ind * 9 + 2];
      const double &R12_fixed = R_all[ind * 9 + 3];
      const double &R22_fixed = R_all[ind * 9 + 4];
      const double &R32_fixed = R_all[ind * 9 + 5];
      const double &R13_fixed = R_all[ind * 9 + 6];
      const double &R23_fixed = R_all[ind * 9 + 7];
      const double &R33_fixed = R_all[ind * 9 + 8];

      const double &offset_x = offset_all[ind * 3 + 0];
      const double &offset_y = offset_all[ind * 3 + 1];
      const double &offset_z = offset_all[ind * 3 + 2];

      // column major
      double &R11 = input_data[ind * size + 5];
      double &R12 = input_data[ind * size + 6];
      double &R13 = input_data[ind * size + 7];
      double &R21 = input_data[ind * size + 8];
      double &R22 = input_data[ind * size + 9];
      double &R23 = input_data[ind * size + 10];
      double &R31 = input_data[ind * size + 11];
      double &R32 = input_data[ind * size + 12];
      double &R33 = input_data[ind * size + 13];


      const double &linear = input_data[ind * size + 0];
      input_data[ind * size + 2] = R13_fixed * linear + offset_x;
      input_data[ind * size + 3] = R23_fixed * linear + offset_y;
      input_data[ind * size + 4] = R33_fixed * linear + offset_z;


    }

    {
      constexpr std::size_t ind = 1;
      // row major
      const double &R11_fixed = R_all[ind * 9 + 0];
      const double &R21_fixed = R_all[ind * 9 + 1];
      const double &R31_fixed = R_all[ind * 9 + 2];
      const double &R12_fixed = R_all[ind * 9 + 3];
      const double &R22_fixed = R_all[ind * 9 + 4];
      const double &R32_fixed = R_all[ind * 9 + 5];
      const double &R13_fixed = R_all[ind * 9 + 6];
      const double &R23_fixed = R_all[ind * 9 + 7];
      const double &R33_fixed = R_all[ind * 9 + 8];

      const double &offset_x = offset_all[ind * 3 + 0];
      const double &offset_y = offset_all[ind * 3 + 1];
      const double &offset_z = offset_all[ind * 3 + 2];

      // column major
      double &R11 = input_data[ind * size + 5];
      double &R12 = input_data[ind * size + 6];
      double &R13 = input_data[ind * size + 7];
      double &R21 = input_data[ind * size + 8];
      double &R22 = input_data[ind * size + 9];
      double &R23 = input_data[ind * size + 10];
      double &R31 = input_data[ind * size + 11];
      double &R32 = input_data[ind * size + 12];
      double &R33 = input_data[ind * size + 13];


      const double &sin_t = input_data[ind * size + 0];
      const double &cos_t = input_data[ind * size + 1];


      // calculate R_cum*R_fixed*R_joint (build column major)

      // column major
      double &R11_old = input_data[(ind - 1) * size + 5];
      double &R12_old = input_data[(ind - 1) * size + 6];
      double &R13_old = input_data[(ind - 1) * size + 7];
      double &R21_old = input_data[(ind - 1) * size + 8];
      double &R22_old = input_data[(ind - 1) * size + 9];
      double &R23_old = input_data[(ind - 1) * size + 10];
      double &R31_old = input_data[(ind - 1) * size + 11];
      double &R32_old = input_data[(ind - 1) * size + 12];
      double &R33_old = input_data[(ind - 1) * size + 13];

      // calculate R_fixed*R_joint (build row major)
      // R_tmp row major
      double &R11_tmp = input_data[ind * size + 5];
      double &R21_tmp = input_data[ind * size + 6];
      double &R31_tmp = input_data[ind * size + 7];
      double &R12_tmp = input_data[ind * size + 8];
      double &R22_tmp = input_data[ind * size + 9];
      double &R32_tmp = input_data[ind * size + 10];
      double &R13_tmp = input_data[ind * size + 11];
      double &R23_tmp = input_data[ind * size + 12];
      double &R33_tmp = input_data[ind * size + 13];

      R11_tmp = R11_fixed * cos_t + R12_fixed * sin_t;
      R21_tmp = R21_fixed * cos_t + R22_fixed * sin_t;
      R31_tmp = R31_fixed * cos_t + R32_fixed * sin_t;
      R12_tmp = -R11_fixed * sin_t + R12_fixed * cos_t;
      R22_tmp = -R21_fixed * sin_t + R22_fixed * cos_t;
      R32_tmp = -R31_fixed * sin_t + R32_fixed * cos_t;
      R13_tmp = R13_fixed;
      R23_tmp = R23_fixed;
      R33_tmp = R33_fixed;

      // R_cum_next current it R_cum*R_fixed*R_joint  (build column major)
      double &tmp1 = input_data[ind * size + 14];
      double &tmp2 = input_data[ind * size + 15];
      double &tmp3 = input_data[ind * size + 16];

      tmp1 = R11_old * R11_tmp + R12_old * R21_tmp + R13_old * R31_tmp;
      tmp2 = R21_old * R11_tmp + R22_old * R21_tmp + R23_old * R31_tmp;
      tmp3 = R31_old * R11_tmp + R32_old * R21_tmp + R33_old * R31_tmp;
      R11 = tmp1;
      R21 = tmp2;
      R31 = tmp3;

      tmp1 = R11_old * R12_tmp + R12_old * R22_tmp + R13_old * R32_tmp;
      tmp2 = R21_old * R12_tmp + R22_old * R22_tmp + R23_old * R32_tmp;
      tmp3 = R31_old * R12_tmp + R32_old * R22_tmp + R33_old * R32_tmp;
      R12 = tmp1;
      R22 = tmp2;
      R32 = tmp3;

      tmp1 = R11_old * R13_tmp + R12_old * R23_tmp + R13_old * R33_tmp;
      tmp2 = R21_old * R13_tmp + R22_old * R23_tmp + R23_old * R33_tmp;
      tmp3 = R31_old * R13_tmp + R32_old * R23_tmp + R33_old * R33_tmp;
      R13 = tmp1;
      R23 = tmp2;
      R33 = tmp3;

      double &px_old = input_data[(ind - 1) * size + 2];
      double &py_old = input_data[(ind - 1) * size + 3];
      double &pz_old = input_data[(ind - 1) * size + 4];

      tmp1 = R11 * offset_x + R12 * offset_y + R13 * offset_z + px_old;
      tmp2 = R21 * offset_x + R22 * offset_y + R23 * offset_z + py_old;
      tmp3 = R31 * offset_x + R32 * offset_y + R33 * offset_z + pz_old;

      input_data[ind * size + 2] = tmp1;
      input_data[ind * size + 3] = tmp2;
      input_data[ind * size + 4] = tmp3;


    }

    {
      constexpr std::size_t ind = 2;
      // row major
      const double &R11_fixed = R_all[ind * 9 + 0];
      const double &R21_fixed = R_all[ind * 9 + 1];
      const double &R31_fixed = R_all[ind * 9 + 2];
      const double &R12_fixed = R_all[ind * 9 + 3];
      const double &R22_fixed = R_all[ind * 9 + 4];
      const double &R32_fixed = R_all[ind * 9 + 5];
      const double &R13_fixed = R_all[ind * 9 + 6];
      const double &R23_fixed = R_all[ind * 9 + 7];
      const double &R33_fixed = R_all[ind * 9 + 8];

      const double &offset_x = offset_all[ind * 3 + 0];
      const double &offset_y = offset_all[ind * 3 + 1];
      const double &offset_z = offset_all[ind * 3 + 2];

      // column major
      double &R11 = input_data[ind * size + 5];
      double &R12 = input_data[ind * size + 6];
      double &R13 = input_data[ind * size + 7];
      double &R21 = input_data[ind * size + 8];
      double &R22 = input_data[ind * size + 9];
      double &R23 = input_data[ind * size + 10];
      double &R31 = input_data[ind * size + 11];
      double &R32 = input_data[ind * size + 12];
      double &R33 = input_data[ind * size + 13];


      const double &sin_t = input_data[ind * size + 0];
      const double &cos_t = input_data[ind * size + 1];


      // calculate R_cum*R_fixed*R_joint (build column major)

      // column major
      double &R11_old = input_data[(ind - 1) * size + 5];
      double &R12_old = input_data[(ind - 1) * size + 6];
      double &R13_old = input_data[(ind - 1) * size + 7];
      double &R21_old = input_data[(ind - 1) * size + 8];
      double &R22_old = input_data[(ind - 1) * size + 9];
      double &R23_old = input_data[(ind - 1) * size + 10];
      double &R31_old = input_data[(ind - 1) * size + 11];
      double &R32_old = input_data[(ind - 1) * size + 12];
      double &R33_old = input_data[(ind - 1) * size + 13];

      // calculate R_fixed*R_joint (build row major)
      // R_tmp row major
      double &R11_tmp = input_data[ind * size + 5];
      double &R21_tmp = input_data[ind * size + 6];
      double &R31_tmp = input_data[ind * size + 7];
      double &R12_tmp = input_data[ind * size + 8];
      double &R22_tmp = input_data[ind * size + 9];
      double &R32_tmp = input_data[ind * size + 10];
      double &R13_tmp = input_data[ind * size + 11];
      double &R23_tmp = input_data[ind * size + 12];
      double &R33_tmp = input_data[ind * size + 13];

      R11_tmp = R11_fixed * cos_t + R12_fixed * sin_t;
      R21_tmp = R21_fixed * cos_t + R22_fixed * sin_t;
      R31_tmp = R31_fixed * cos_t + R32_fixed * sin_t;
      R12_tmp = -R11_fixed * sin_t + R12_fixed * cos_t;
      R22_tmp = -R21_fixed * sin_t + R22_fixed * cos_t;
      R32_tmp = -R31_fixed * sin_t + R32_fixed * cos_t;
      R13_tmp = R13_fixed;
      R23_tmp = R23_fixed;
      R33_tmp = R33_fixed;

      // R_cum_next current it R_cum*R_fixed*R_joint  (build column major)
      double &tmp1 = input_data[ind * size + 14];
      double &tmp2 = input_data[ind * size + 15];
      double &tmp3 = input_data[ind * size + 16];

      tmp1 = R11_old * R11_tmp + R12_old * R21_tmp + R13_old * R31_tmp;
      tmp2 = R21_old * R11_tmp + R22_old * R21_tmp + R23_old * R31_tmp;
      tmp3 = R31_old * R11_tmp + R32_old * R21_tmp + R33_old * R31_tmp;
      R11 = tmp1;
      R21 = tmp2;
      R31 = tmp3;

      tmp1 = R11_old * R12_tmp + R12_old * R22_tmp + R13_old * R32_tmp;
      tmp2 = R21_old * R12_tmp + R22_old * R22_tmp + R23_old * R32_tmp;
      tmp3 = R31_old * R12_tmp + R32_old * R22_tmp + R33_old * R32_tmp;
      R12 = tmp1;
      R22 = tmp2;
      R32 = tmp3;

      tmp1 = R11_old * R13_tmp + R12_old * R23_tmp + R13_old * R33_tmp;
      tmp2 = R21_old * R13_tmp + R22_old * R23_tmp + R23_old * R33_tmp;
      tmp3 = R31_old * R13_tmp + R32_old * R23_tmp + R33_old * R33_tmp;
      R13 = tmp1;
      R23 = tmp2;
      R33 = tmp3;

      double &px_old = input_data[(ind - 1) * size + 2];
      double &py_old = input_data[(ind - 1) * size + 3];
      double &pz_old = input_data[(ind - 1) * size + 4];

      tmp1 = R11 * offset_x + R12 * offset_y + R13 * offset_z + px_old;
      tmp2 = R21 * offset_x + R22 * offset_y + R23 * offset_z + py_old;
      tmp3 = R31 * offset_x + R32 * offset_y + R33 * offset_z + pz_old;

      input_data[ind * size + 2] = tmp1;
      input_data[ind * size + 3] = tmp2;
      input_data[ind * size + 4] = tmp3;


    }

    {
      constexpr std::size_t ind = 3;
      // row major
      const double &R11_fixed = R_all[ind * 9 + 0];
      const double &R21_fixed = R_all[ind * 9 + 1];
      const double &R31_fixed = R_all[ind * 9 + 2];
      const double &R12_fixed = R_all[ind * 9 + 3];
      const double &R22_fixed = R_all[ind * 9 + 4];
      const double &R32_fixed = R_all[ind * 9 + 5];
      const double &R13_fixed = R_all[ind * 9 + 6];
      const double &R23_fixed = R_all[ind * 9 + 7];
      const double &R33_fixed = R_all[ind * 9 + 8];

      const double &offset_x = offset_all[ind * 3 + 0];
      const double &offset_y = offset_all[ind * 3 + 1];
      const double &offset_z = offset_all[ind * 3 + 2];

      // column major
      double &R11 = input_data[ind * size + 5];
      double &R12 = input_data[ind * size + 6];
      double &R13 = input_data[ind * size + 7];
      double &R21 = input_data[ind * size + 8];
      double &R22 = input_data[ind * size + 9];
      double &R23 = input_data[ind * size + 10];
      double &R31 = input_data[ind * size + 11];
      double &R32 = input_data[ind * size + 12];
      double &R33 = input_data[ind * size + 13];


      const double &sin_t = input_data[ind * size + 0];
      const double &cos_t = input_data[ind * size + 1];


      // calculate R_cum*R_fixed*R_joint (build column major)

      // column major
      double &R11_old = input_data[(ind - 1) * size + 5];
      double &R12_old = input_data[(ind - 1) * size + 6];
      double &R13_old = input_data[(ind - 1) * size + 7];
      double &R21_old = input_data[(ind - 1) * size + 8];
      double &R22_old = input_data[(ind - 1) * size + 9];
      double &R23_old = input_data[(ind - 1) * size + 10];
      double &R31_old = input_data[(ind - 1) * size + 11];
      double &R32_old = input_data[(ind - 1) * size + 12];
      double &R33_old = input_data[(ind - 1) * size + 13];

      // calculate R_fixed*R_joint (build row major)
      // R_tmp row major
      double &R11_tmp = input_data[ind * size + 5];
      double &R21_tmp = input_data[ind * size + 6];
      double &R31_tmp = input_data[ind * size + 7];
      double &R12_tmp = input_data[ind * size + 8];
      double &R22_tmp = input_data[ind * size + 9];
      double &R32_tmp = input_data[ind * size + 10];
      double &R13_tmp = input_data[ind * size + 11];
      double &R23_tmp = input_data[ind * size + 12];
      double &R33_tmp = input_data[ind * size + 13];

      R11_tmp = R11_fixed * cos_t + R12_fixed * sin_t;
      R21_tmp = R21_fixed * cos_t + R22_fixed * sin_t;
      R31_tmp = R31_fixed * cos_t + R32_fixed * sin_t;
      R12_tmp = -R11_fixed * sin_t + R12_fixed * cos_t;
      R22_tmp = -R21_fixed * sin_t + R22_fixed * cos_t;
      R32_tmp = -R31_fixed * sin_t + R32_fixed * cos_t;
      R13_tmp = R13_fixed;
      R23_tmp = R23_fixed;
      R33_tmp = R33_fixed;

      // R_cum_next current it R_cum*R_fixed*R_joint  (build column major)
      double &tmp1 = input_data[ind * size + 14];
      double &tmp2 = input_data[ind * size + 15];
      double &tmp3 = input_data[ind * size + 16];

      tmp1 = R11_old * R11_tmp + R12_old * R21_tmp + R13_old * R31_tmp;
      tmp2 = R21_old * R11_tmp + R22_old * R21_tmp + R23_old * R31_tmp;
      tmp3 = R31_old * R11_tmp + R32_old * R21_tmp + R33_old * R31_tmp;
      R11 = tmp1;
      R21 = tmp2;
      R31 = tmp3;

      tmp1 = R11_old * R12_tmp + R12_old * R22_tmp + R13_old * R32_tmp;
      tmp2 = R21_old * R12_tmp + R22_old * R22_tmp + R23_old * R32_tmp;
      tmp3 = R31_old * R12_tmp + R32_old * R22_tmp + R33_old * R32_tmp;
      R12 = tmp1;
      R22 = tmp2;
      R32 = tmp3;

      tmp1 = R11_old * R13_tmp + R12_old * R23_tmp + R13_old * R33_tmp;
      tmp2 = R21_old * R13_tmp + R22_old * R23_tmp + R23_old * R33_tmp;
      tmp3 = R31_old * R13_tmp + R32_old * R23_tmp + R33_old * R33_tmp;
      R13 = tmp1;
      R23 = tmp2;
      R33 = tmp3;

      double &px_old = input_data[(ind - 1) * size + 2];
      double &py_old = input_data[(ind - 1) * size + 3];
      double &pz_old = input_data[(ind - 1) * size + 4];

      tmp1 = R11 * offset_x + R12 * offset_y + R13 * offset_z + px_old;
      tmp2 = R21 * offset_x + R22 * offset_y + R23 * offset_z + py_old;
      tmp3 = R31 * offset_x + R32 * offset_y + R33 * offset_z + pz_old;

      input_data[ind * size + 2] = tmp1;
      input_data[ind * size + 3] = tmp2;
      input_data[ind * size + 4] = tmp3;


    }

    {
      constexpr std::size_t ind = 4;
      // row major
      const double &R11_fixed = R_all[ind * 9 + 0];
      const double &R21_fixed = R_all[ind * 9 + 1];
      const double &R31_fixed = R_all[ind * 9 + 2];
      const double &R12_fixed = R_all[ind * 9 + 3];
      const double &R22_fixed = R_all[ind * 9 + 4];
      const double &R32_fixed = R_all[ind * 9 + 5];
      const double &R13_fixed = R_all[ind * 9 + 6];
      const double &R23_fixed = R_all[ind * 9 + 7];
      const double &R33_fixed = R_all[ind * 9 + 8];

      const double &offset_x = offset_all[ind * 3 + 0];
      const double &offset_y = offset_all[ind * 3 + 1];
      const double &offset_z = offset_all[ind * 3 + 2];

      // column major
      double &R11 = input_data[ind * size + 5];
      double &R12 = input_data[ind * size + 6];
      double &R13 = input_data[ind * size + 7];
      double &R21 = input_data[ind * size + 8];
      double &R22 = input_data[ind * size + 9];
      double &R23 = input_data[ind * size + 10];
      double &R31 = input_data[ind * size + 11];
      double &R32 = input_data[ind * size + 12];
      double &R33 = input_data[ind * size + 13];


      const double &sin_t = input_data[ind * size + 0];
      const double &cos_t = input_data[ind * size + 1];


      // calculate R_cum*R_fixed*R_joint (build column major)

      // column major
      double &R11_old = input_data[(ind - 1) * size + 5];
      double &R12_old = input_data[(ind - 1) * size + 6];
      double &R13_old = input_data[(ind - 1) * size + 7];
      double &R21_old = input_data[(ind - 1) * size + 8];
      double &R22_old = input_data[(ind - 1) * size + 9];
      double &R23_old = input_data[(ind - 1) * size + 10];
      double &R31_old = input_data[(ind - 1) * size + 11];
      double &R32_old = input_data[(ind - 1) * size + 12];
      double &R33_old = input_data[(ind - 1) * size + 13];

      // calculate R_fixed*R_joint (build row major)
      // R_tmp row major
      double &R11_tmp = input_data[ind * size + 5];
      double &R21_tmp = input_data[ind * size + 6];
      double &R31_tmp = input_data[ind * size + 7];
      double &R12_tmp = input_data[ind * size + 8];
      double &R22_tmp = input_data[ind * size + 9];
      double &R32_tmp = input_data[ind * size + 10];
      double &R13_tmp = input_data[ind * size + 11];
      double &R23_tmp = input_data[ind * size + 12];
      double &R33_tmp = input_data[ind * size + 13];

      R11_tmp = R11_fixed * cos_t + R12_fixed * sin_t;
      R21_tmp = R21_fixed * cos_t + R22_fixed * sin_t;
      R31_tmp = R31_fixed * cos_t + R32_fixed * sin_t;
      R12_tmp = -R11_fixed * sin_t + R12_fixed * cos_t;
      R22_tmp = -R21_fixed * sin_t + R22_fixed * cos_t;
      R32_tmp = -R31_fixed * sin_t + R32_fixed * cos_t;
      R13_tmp = R13_fixed;
      R23_tmp = R23_fixed;
      R33_tmp = R33_fixed;

      // R_cum_next current it R_cum*R_fixed*R_joint  (build column major)
      double &tmp1 = input_data[ind * size + 14];
      double &tmp2 = input_data[ind * size + 15];
      double &tmp3 = input_data[ind * size + 16];

      tmp1 = R11_old * R11_tmp + R12_old * R21_tmp + R13_old * R31_tmp;
      tmp2 = R21_old * R11_tmp + R22_old * R21_tmp + R23_old * R31_tmp;
      tmp3 = R31_old * R11_tmp + R32_old * R21_tmp + R33_old * R31_tmp;
      R11 = tmp1;
      R21 = tmp2;
      R31 = tmp3;

      tmp1 = R11_old * R12_tmp + R12_old * R22_tmp + R13_old * R32_tmp;
      tmp2 = R21_old * R12_tmp + R22_old * R22_tmp + R23_old * R32_tmp;
      tmp3 = R31_old * R12_tmp + R32_old * R22_tmp + R33_old * R32_tmp;
      R12 = tmp1;
      R22 = tmp2;
      R32 = tmp3;

      tmp1 = R11_old * R13_tmp + R12_old * R23_tmp + R13_old * R33_tmp;
      tmp2 = R21_old * R13_tmp + R22_old * R23_tmp + R23_old * R33_tmp;
      tmp3 = R31_old * R13_tmp + R32_old * R23_tmp + R33_old * R33_tmp;
      R13 = tmp1;
      R23 = tmp2;
      R33 = tmp3;

      double &px_old = input_data[(ind - 1) * size + 2];
      double &py_old = input_data[(ind - 1) * size + 3];
      double &pz_old = input_data[(ind - 1) * size + 4];

      tmp1 = R11 * offset_x + R12 * offset_y + R13 * offset_z + px_old;
      tmp2 = R21 * offset_x + R22 * offset_y + R23 * offset_z + py_old;
      tmp3 = R31 * offset_x + R32 * offset_y + R33 * offset_z + pz_old;

      input_data[ind * size + 2] = tmp1;
      input_data[ind * size + 3] = tmp2;
      input_data[ind * size + 4] = tmp3;


    }

    {
      constexpr std::size_t ind = 5;
      // row major
      const double &R11_fixed = R_all[ind * 9 + 0];
      const double &R21_fixed = R_all[ind * 9 + 1];
      const double &R31_fixed = R_all[ind * 9 + 2];
      const double &R12_fixed = R_all[ind * 9 + 3];
      const double &R22_fixed = R_all[ind * 9 + 4];
      const double &R32_fixed = R_all[ind * 9 + 5];
      const double &R13_fixed = R_all[ind * 9 + 6];
      const double &R23_fixed = R_all[ind * 9 + 7];
      const double &R33_fixed = R_all[ind * 9 + 8];

      const double &offset_x = offset_all[ind * 3 + 0];
      const double &offset_y = offset_all[ind * 3 + 1];
      const double &offset_z = offset_all[ind * 3 + 2];

      // column major
      double &R11 = input_data[ind * size + 5];
      double &R12 = input_data[ind * size + 6];
      double &R13 = input_data[ind * size + 7];
      double &R21 = input_data[ind * size + 8];
      double &R22 = input_data[ind * size + 9];
      double &R23 = input_data[ind * size + 10];
      double &R31 = input_data[ind * size + 11];
      double &R32 = input_data[ind * size + 12];
      double &R33 = input_data[ind * size + 13];


      const double &sin_t = input_data[ind * size + 0];
      const double &cos_t = input_data[ind * size + 1];


      // calculate R_cum*R_fixed*R_joint (build column major)

      // column major
      double &R11_old = input_data[(ind - 1) * size + 5];
      double &R12_old = input_data[(ind - 1) * size + 6];
      double &R13_old = input_data[(ind - 1) * size + 7];
      double &R21_old = input_data[(ind - 1) * size + 8];
      double &R22_old = input_data[(ind - 1) * size + 9];
      double &R23_old = input_data[(ind - 1) * size + 10];
      double &R31_old = input_data[(ind - 1) * size + 11];
      double &R32_old = input_data[(ind - 1) * size + 12];
      double &R33_old = input_data[(ind - 1) * size + 13];

      // calculate R_fixed*R_joint (build row major)
      // R_tmp row major
      double &R11_tmp = input_data[ind * size + 5];
      double &R21_tmp = input_data[ind * size + 6];
      double &R31_tmp = input_data[ind * size + 7];
      double &R12_tmp = input_data[ind * size + 8];
      double &R22_tmp = input_data[ind * size + 9];
      double &R32_tmp = input_data[ind * size + 10];
      double &R13_tmp = input_data[ind * size + 11];
      double &R23_tmp = input_data[ind * size + 12];
      double &R33_tmp = input_data[ind * size + 13];

      R11_tmp = R11_fixed * cos_t + R12_fixed * sin_t;
      R21_tmp = R21_fixed * cos_t + R22_fixed * sin_t;
      R31_tmp = R31_fixed * cos_t + R32_fixed * sin_t;
      R12_tmp = -R11_fixed * sin_t + R12_fixed * cos_t;
      R22_tmp = -R21_fixed * sin_t + R22_fixed * cos_t;
      R32_tmp = -R31_fixed * sin_t + R32_fixed * cos_t;
      R13_tmp = R13_fixed;
      R23_tmp = R23_fixed;
      R33_tmp = R33_fixed;

      // R_cum_next current it R_cum*R_fixed*R_joint  (build column major)
      double &tmp1 = input_data[ind * size + 14];
      double &tmp2 = input_data[ind * size + 15];
      double &tmp3 = input_data[ind * size + 16];

      tmp1 = R11_old * R11_tmp + R12_old * R21_tmp + R13_old * R31_tmp;
      tmp2 = R21_old * R11_tmp + R22_old * R21_tmp + R23_old * R31_tmp;
      tmp3 = R31_old * R11_tmp + R32_old * R21_tmp + R33_old * R31_tmp;
      R11 = tmp1;
      R21 = tmp2;
      R31 = tmp3;

      tmp1 = R11_old * R12_tmp + R12_old * R22_tmp + R13_old * R32_tmp;
      tmp2 = R21_old * R12_tmp + R22_old * R22_tmp + R23_old * R32_tmp;
      tmp3 = R31_old * R12_tmp + R32_old * R22_tmp + R33_old * R32_tmp;
      R12 = tmp1;
      R22 = tmp2;
      R32 = tmp3;

      tmp1 = R11_old * R13_tmp + R12_old * R23_tmp + R13_old * R33_tmp;
      tmp2 = R21_old * R13_tmp + R22_old * R23_tmp + R23_old * R33_tmp;
      tmp3 = R31_old * R13_tmp + R32_old * R23_tmp + R33_old * R33_tmp;
      R13 = tmp1;
      R23 = tmp2;
      R33 = tmp3;

      double &px_old = input_data[(ind - 1) * size + 2];
      double &py_old = input_data[(ind - 1) * size + 3];
      double &pz_old = input_data[(ind - 1) * size + 4];

      tmp1 = R11 * offset_x + R12 * offset_y + R13 * offset_z + px_old;
      tmp2 = R21 * offset_x + R22 * offset_y + R23 * offset_z + py_old;
      tmp3 = R31 * offset_x + R32 * offset_y + R33 * offset_z + pz_old;

      input_data[ind * size + 2] = tmp1;
      input_data[ind * size + 3] = tmp2;
      input_data[ind * size + 4] = tmp3;


    }

    {
      constexpr std::size_t ind = 6;
      // row major
      const double &R11_fixed = R_all[ind * 9 + 0];
      const double &R21_fixed = R_all[ind * 9 + 1];
      const double &R31_fixed = R_all[ind * 9 + 2];
      const double &R12_fixed = R_all[ind * 9 + 3];
      const double &R22_fixed = R_all[ind * 9 + 4];
      const double &R32_fixed = R_all[ind * 9 + 5];
      const double &R13_fixed = R_all[ind * 9 + 6];
      const double &R23_fixed = R_all[ind * 9 + 7];
      const double &R33_fixed = R_all[ind * 9 + 8];

      const double &offset_x = offset_all[ind * 3 + 0];
      const double &offset_y = offset_all[ind * 3 + 1];
      const double &offset_z = offset_all[ind * 3 + 2];

      // column major
      double &R11 = input_data[ind * size + 5];
      double &R12 = input_data[ind * size + 6];
      double &R13 = input_data[ind * size + 7];
      double &R21 = input_data[ind * size + 8];
      double &R22 = input_data[ind * size + 9];
      double &R23 = input_data[ind * size + 10];
      double &R31 = input_data[ind * size + 11];
      double &R32 = input_data[ind * size + 12];
      double &R33 = input_data[ind * size + 13];


      const double &sin_t = input_data[ind * size + 0];
      const double &cos_t = input_data[ind * size + 1];


      // calculate R_cum*R_fixed*R_joint (build column major)

      // column major
      double &R11_old = input_data[(ind - 1) * size + 5];
      double &R12_old = input_data[(ind - 1) * size + 6];
      double &R13_old = input_data[(ind - 1) * size + 7];
      double &R21_old = input_data[(ind - 1) * size + 8];
      double &R22_old = input_data[(ind - 1) * size + 9];
      double &R23_old = input_data[(ind - 1) * size + 10];
      double &R31_old = input_data[(ind - 1) * size + 11];
      double &R32_old = input_data[(ind - 1) * size + 12];
      double &R33_old = input_data[(ind - 1) * size + 13];

      // calculate R_fixed*R_joint (build row major)
      // R_tmp row major
      double &R11_tmp = input_data[ind * size + 5];
      double &R21_tmp = input_data[ind * size + 6];
      double &R31_tmp = input_data[ind * size + 7];
      double &R12_tmp = input_data[ind * size + 8];
      double &R22_tmp = input_data[ind * size + 9];
      double &R32_tmp = input_data[ind * size + 10];
      double &R13_tmp = input_data[ind * size + 11];
      double &R23_tmp = input_data[ind * size + 12];
      double &R33_tmp = input_data[ind * size + 13];

      R11_tmp = R11_fixed * cos_t + R12_fixed * sin_t;
      R21_tmp = R21_fixed * cos_t + R22_fixed * sin_t;
      R31_tmp = R31_fixed * cos_t + R32_fixed * sin_t;
      R12_tmp = -R11_fixed * sin_t + R12_fixed * cos_t;
      R22_tmp = -R21_fixed * sin_t + R22_fixed * cos_t;
      R32_tmp = -R31_fixed * sin_t + R32_fixed * cos_t;
      R13_tmp = R13_fixed;
      R23_tmp = R23_fixed;
      R33_tmp = R33_fixed;

      // R_cum_next current it R_cum*R_fixed*R_joint  (build column major)
      double &tmp1 = input_data[ind * size + 14];
      double &tmp2 = input_data[ind * size + 15];
      double &tmp3 = input_data[ind * size + 16];

      tmp1 = R11_old * R11_tmp + R12_old * R21_tmp + R13_old * R31_tmp;
      tmp2 = R21_old * R11_tmp + R22_old * R21_tmp + R23_old * R31_tmp;
      tmp3 = R31_old * R11_tmp + R32_old * R21_tmp + R33_old * R31_tmp;
      R11 = tmp1;
      R21 = tmp2;
      R31 = tmp3;

      tmp1 = R11_old * R12_tmp + R12_old * R22_tmp + R13_old * R32_tmp;
      tmp2 = R21_old * R12_tmp + R22_old * R22_tmp + R23_old * R32_tmp;
      tmp3 = R31_old * R12_tmp + R32_old * R22_tmp + R33_old * R32_tmp;
      R12 = tmp1;
      R22 = tmp2;
      R32 = tmp3;

      tmp1 = R11_old * R13_tmp + R12_old * R23_tmp + R13_old * R33_tmp;
      tmp2 = R21_old * R13_tmp + R22_old * R23_tmp + R23_old * R33_tmp;
      tmp3 = R31_old * R13_tmp + R32_old * R23_tmp + R33_old * R33_tmp;
      R13 = tmp1;
      R23 = tmp2;
      R33 = tmp3;

      double &px_old = input_data[(ind - 1) * size + 2];
      double &py_old = input_data[(ind - 1) * size + 3];
      double &pz_old = input_data[(ind - 1) * size + 4];

      tmp1 = R11 * offset_x + R12 * offset_y + R13 * offset_z + px_old;
      tmp2 = R21 * offset_x + R22 * offset_y + R23 * offset_z + py_old;
      tmp3 = R31 * offset_x + R32 * offset_y + R33 * offset_z + pz_old;

      input_data[ind * size + 2] = tmp1;
      input_data[ind * size + 3] = tmp2;
      input_data[ind * size + 4] = tmp3;


    }

    {
      constexpr std::size_t ind = 7;
      // row major
      const double &R11_fixed = R_all[ind * 9 + 0];
      const double &R21_fixed = R_all[ind * 9 + 1];
      const double &R31_fixed = R_all[ind * 9 + 2];
      const double &R12_fixed = R_all[ind * 9 + 3];
      const double &R22_fixed = R_all[ind * 9 + 4];
      const double &R32_fixed = R_all[ind * 9 + 5];
      const double &R13_fixed = R_all[ind * 9 + 6];
      const double &R23_fixed = R_all[ind * 9 + 7];
      const double &R33_fixed = R_all[ind * 9 + 8];

      const double &offset_x = offset_all[ind * 3 + 0];
      const double &offset_y = offset_all[ind * 3 + 1];
      const double &offset_z = offset_all[ind * 3 + 2];

      // column major
      double &R11 = input_data[ind * size + 5];
      double &R12 = input_data[ind * size + 6];
      double &R13 = input_data[ind * size + 7];
      double &R21 = input_data[ind * size + 8];
      double &R22 = input_data[ind * size + 9];
      double &R23 = input_data[ind * size + 10];
      double &R31 = input_data[ind * size + 11];
      double &R32 = input_data[ind * size + 12];
      double &R33 = input_data[ind * size + 13];


      const double &sin_t = input_data[ind * size + 0];
      const double &cos_t = input_data[ind * size + 1];


      // calculate R_cum*R_fixed*R_joint (build column major)

      // column major
      double &R11_old = input_data[(ind - 1) * size + 5];
      double &R12_old = input_data[(ind - 1) * size + 6];
      double &R13_old = input_data[(ind - 1) * size + 7];
      double &R21_old = input_data[(ind - 1) * size + 8];
      double &R22_old = input_data[(ind - 1) * size + 9];
      double &R23_old = input_data[(ind - 1) * size + 10];
      double &R31_old = input_data[(ind - 1) * size + 11];
      double &R32_old = input_data[(ind - 1) * size + 12];
      double &R33_old = input_data[(ind - 1) * size + 13];

      // calculate R_fixed*R_joint (build row major)
      // R_tmp row major
      double &R11_tmp = input_data[ind * size + 5];
      double &R21_tmp = input_data[ind * size + 6];
      double &R31_tmp = input_data[ind * size + 7];
      double &R12_tmp = input_data[ind * size + 8];
      double &R22_tmp = input_data[ind * size + 9];
      double &R32_tmp = input_data[ind * size + 10];
      double &R13_tmp = input_data[ind * size + 11];
      double &R23_tmp = input_data[ind * size + 12];
      double &R33_tmp = input_data[ind * size + 13];

      R11_tmp = R11_fixed * cos_t + R12_fixed * sin_t;
      R21_tmp = R21_fixed * cos_t + R22_fixed * sin_t;
      R31_tmp = R31_fixed * cos_t + R32_fixed * sin_t;
      R12_tmp = -R11_fixed * sin_t + R12_fixed * cos_t;
      R22_tmp = -R21_fixed * sin_t + R22_fixed * cos_t;
      R32_tmp = -R31_fixed * sin_t + R32_fixed * cos_t;
      R13_tmp = R13_fixed;
      R23_tmp = R23_fixed;
      R33_tmp = R33_fixed;

      // R_cum_next current it R_cum*R_fixed*R_joint  (build column major)
      double &tmp1 = input_data[ind * size + 14];
      double &tmp2 = input_data[ind * size + 15];
      double &tmp3 = input_data[ind * size + 16];

      tmp1 = R11_old * R11_tmp + R12_old * R21_tmp + R13_old * R31_tmp;
      tmp2 = R21_old * R11_tmp + R22_old * R21_tmp + R23_old * R31_tmp;
      tmp3 = R31_old * R11_tmp + R32_old * R21_tmp + R33_old * R31_tmp;
      R11 = tmp1;
      R21 = tmp2;
      R31 = tmp3;

      tmp1 = R11_old * R12_tmp + R12_old * R22_tmp + R13_old * R32_tmp;
      tmp2 = R21_old * R12_tmp + R22_old * R22_tmp + R23_old * R32_tmp;
      tmp3 = R31_old * R12_tmp + R32_old * R22_tmp + R33_old * R32_tmp;
      R12 = tmp1;
      R22 = tmp2;
      R32 = tmp3;

      tmp1 = R11_old * R13_tmp + R12_old * R23_tmp + R13_old * R33_tmp;
      tmp2 = R21_old * R13_tmp + R22_old * R23_tmp + R23_old * R33_tmp;
      tmp3 = R31_old * R13_tmp + R32_old * R23_tmp + R33_old * R33_tmp;
      R13 = tmp1;
      R23 = tmp2;
      R33 = tmp3;

      double &px_old = input_data[(ind - 1) * size + 2];
      double &py_old = input_data[(ind - 1) * size + 3];
      double &pz_old = input_data[(ind - 1) * size + 4];

      tmp1 = R11 * offset_x + R12 * offset_y + R13 * offset_z + px_old;
      tmp2 = R21 * offset_x + R22 * offset_y + R23 * offset_z + py_old;
      tmp3 = R31 * offset_x + R32 * offset_y + R33 * offset_z + pz_old;

      input_data[ind * size + 2] = tmp1;
      input_data[ind * size + 3] = tmp2;
      input_data[ind * size + 4] = tmp3;


    }

    {
      constexpr std::size_t ind = 8;
      // row major
      const double &R11_fixed = R_all[ind * 9 + 0];
      const double &R21_fixed = R_all[ind * 9 + 1];
      const double &R31_fixed = R_all[ind * 9 + 2];
      const double &R12_fixed = R_all[ind * 9 + 3];
      const double &R22_fixed = R_all[ind * 9 + 4];
      const double &R32_fixed = R_all[ind * 9 + 5];
      const double &R13_fixed = R_all[ind * 9 + 6];
      const double &R23_fixed = R_all[ind * 9 + 7];
      const double &R33_fixed = R_all[ind * 9 + 8];

      const double &offset_x = offset_all[ind * 3 + 0];
      const double &offset_y = offset_all[ind * 3 + 1];
      const double &offset_z = offset_all[ind * 3 + 2];

      // column major
      double &R11 = input_data[ind * size + 5];
      double &R12 = input_data[ind * size + 6];
      double &R13 = input_data[ind * size + 7];
      double &R21 = input_data[ind * size + 8];
      double &R22 = input_data[ind * size + 9];
      double &R23 = input_data[ind * size + 10];
      double &R31 = input_data[ind * size + 11];
      double &R32 = input_data[ind * size + 12];
      double &R33 = input_data[ind * size + 13];


      const double &sin_t = input_data[ind * size + 0];
      const double &cos_t = input_data[ind * size + 1];


      // calculate R_cum*R_fixed*R_joint (build column major)

      // column major
      double &R11_old = input_data[(ind - 1) * size + 5];
      double &R12_old = input_data[(ind - 1) * size + 6];
      double &R13_old = input_data[(ind - 1) * size + 7];
      double &R21_old = input_data[(ind - 1) * size + 8];
      double &R22_old = input_data[(ind - 1) * size + 9];
      double &R23_old = input_data[(ind - 1) * size + 10];
      double &R31_old = input_data[(ind - 1) * size + 11];
      double &R32_old = input_data[(ind - 1) * size + 12];
      double &R33_old = input_data[(ind - 1) * size + 13];

      // calculate R_fixed*R_joint (build row major)
      // R_tmp row major
      double &R11_tmp = input_data[ind * size + 5];
      double &R21_tmp = input_data[ind * size + 6];
      double &R31_tmp = input_data[ind * size + 7];
      double &R12_tmp = input_data[ind * size + 8];
      double &R22_tmp = input_data[ind * size + 9];
      double &R32_tmp = input_data[ind * size + 10];
      double &R13_tmp = input_data[ind * size + 11];
      double &R23_tmp = input_data[ind * size + 12];
      double &R33_tmp = input_data[ind * size + 13];

      R11_tmp = R11_fixed * cos_t + R12_fixed * sin_t;
      R21_tmp = R21_fixed * cos_t + R22_fixed * sin_t;
      R31_tmp = R31_fixed * cos_t + R32_fixed * sin_t;
      R12_tmp = -R11_fixed * sin_t + R12_fixed * cos_t;
      R22_tmp = -R21_fixed * sin_t + R22_fixed * cos_t;
      R32_tmp = -R31_fixed * sin_t + R32_fixed * cos_t;
      R13_tmp = R13_fixed;
      R23_tmp = R23_fixed;
      R33_tmp = R33_fixed;

      // R_cum_next current it R_cum*R_fixed*R_joint  (build column major)
      double &tmp1 = input_data[ind * size + 14];
      double &tmp2 = input_data[ind * size + 15];
      double &tmp3 = input_data[ind * size + 16];

      tmp1 = R11_old * R11_tmp + R12_old * R21_tmp + R13_old * R31_tmp;
      tmp2 = R21_old * R11_tmp + R22_old * R21_tmp + R23_old * R31_tmp;
      tmp3 = R31_old * R11_tmp + R32_old * R21_tmp + R33_old * R31_tmp;
      R11 = tmp1;
      R21 = tmp2;
      R31 = tmp3;

      tmp1 = R11_old * R12_tmp + R12_old * R22_tmp + R13_old * R32_tmp;
      tmp2 = R21_old * R12_tmp + R22_old * R22_tmp + R23_old * R32_tmp;
      tmp3 = R31_old * R12_tmp + R32_old * R22_tmp + R33_old * R32_tmp;
      R12 = tmp1;
      R22 = tmp2;
      R32 = tmp3;

      tmp1 = R11_old * R13_tmp + R12_old * R23_tmp + R13_old * R33_tmp;
      tmp2 = R21_old * R13_tmp + R22_old * R23_tmp + R23_old * R33_tmp;
      tmp3 = R31_old * R13_tmp + R32_old * R23_tmp + R33_old * R33_tmp;
      R13 = tmp1;
      R23 = tmp2;
      R33 = tmp3;

      double &px_old = input_data[(ind - 1) * size + 2];
      double &py_old = input_data[(ind - 1) * size + 3];
      double &pz_old = input_data[(ind - 1) * size + 4];

      tmp1 = R11 * offset_x + R12 * offset_y + R13 * offset_z + px_old;
      tmp2 = R21 * offset_x + R22 * offset_y + R23 * offset_z + py_old;
      tmp3 = R31 * offset_x + R32 * offset_y + R33 * offset_z + pz_old;

      input_data[ind * size + 2] = tmp1;
      input_data[ind * size + 3] = tmp2;
      input_data[ind * size + 4] = tmp3;


    }

    {
      constexpr std::size_t ind = 9;
      // row major
      const double &R11_fixed = R_all[ind * 9 + 0];
      const double &R21_fixed = R_all[ind * 9 + 1];
      const double &R31_fixed = R_all[ind * 9 + 2];
      const double &R12_fixed = R_all[ind * 9 + 3];
      const double &R22_fixed = R_all[ind * 9 + 4];
      const double &R32_fixed = R_all[ind * 9 + 5];
      const double &R13_fixed = R_all[ind * 9 + 6];
      const double &R23_fixed = R_all[ind * 9 + 7];
      const double &R33_fixed = R_all[ind * 9 + 8];

      const double &offset_x = offset_all[ind * 3 + 0];
      const double &offset_y = offset_all[ind * 3 + 1];
      const double &offset_z = offset_all[ind * 3 + 2];

      // column major
      double &R11 = input_data[ind * size + 5];
      double &R12 = input_data[ind * size + 6];
      double &R13 = input_data[ind * size + 7];
      double &R21 = input_data[ind * size + 8];
      double &R22 = input_data[ind * size + 9];
      double &R23 = input_data[ind * size + 10];
      double &R31 = input_data[ind * size + 11];
      double &R32 = input_data[ind * size + 12];
      double &R33 = input_data[ind * size + 13];


      const double &sin_t = input_data[ind * size + 0];
      const double &cos_t = input_data[ind * size + 1];


      // calculate R_cum*R_fixed*R_joint (build column major)

      // column major
      double &R11_old = input_data[(ind - 1) * size + 5];
      double &R12_old = input_data[(ind - 1) * size + 6];
      double &R13_old = input_data[(ind - 1) * size + 7];
      double &R21_old = input_data[(ind - 1) * size + 8];
      double &R22_old = input_data[(ind - 1) * size + 9];
      double &R23_old = input_data[(ind - 1) * size + 10];
      double &R31_old = input_data[(ind - 1) * size + 11];
      double &R32_old = input_data[(ind - 1) * size + 12];
      double &R33_old = input_data[(ind - 1) * size + 13];

      // calculate R_fixed*R_joint (build row major)
      // R_tmp row major
      double &R11_tmp = input_data[ind * size + 5];
      double &R21_tmp = input_data[ind * size + 6];
      double &R31_tmp = input_data[ind * size + 7];
      double &R12_tmp = input_data[ind * size + 8];
      double &R22_tmp = input_data[ind * size + 9];
      double &R32_tmp = input_data[ind * size + 10];
      double &R13_tmp = input_data[ind * size + 11];
      double &R23_tmp = input_data[ind * size + 12];
      double &R33_tmp = input_data[ind * size + 13];

      R11_tmp = R11_fixed * cos_t + R12_fixed * sin_t;
      R21_tmp = R21_fixed * cos_t + R22_fixed * sin_t;
      R31_tmp = R31_fixed * cos_t + R32_fixed * sin_t;
      R12_tmp = -R11_fixed * sin_t + R12_fixed * cos_t;
      R22_tmp = -R21_fixed * sin_t + R22_fixed * cos_t;
      R32_tmp = -R31_fixed * sin_t + R32_fixed * cos_t;
      R13_tmp = R13_fixed;
      R23_tmp = R23_fixed;
      R33_tmp = R33_fixed;

      // R_cum_next current it R_cum*R_fixed*R_joint  (build column major)
      double &tmp1 = input_data[ind * size + 14];
      double &tmp2 = input_data[ind * size + 15];
      double &tmp3 = input_data[ind * size + 16];

      tmp1 = R11_old * R11_tmp + R12_old * R21_tmp + R13_old * R31_tmp;
      tmp2 = R21_old * R11_tmp + R22_old * R21_tmp + R23_old * R31_tmp;
      tmp3 = R31_old * R11_tmp + R32_old * R21_tmp + R33_old * R31_tmp;
      R11 = tmp1;
      R21 = tmp2;
      R31 = tmp3;

      tmp1 = R11_old * R12_tmp + R12_old * R22_tmp + R13_old * R32_tmp;
      tmp2 = R21_old * R12_tmp + R22_old * R22_tmp + R23_old * R32_tmp;
      tmp3 = R31_old * R12_tmp + R32_old * R22_tmp + R33_old * R32_tmp;
      R12 = tmp1;
      R22 = tmp2;
      R32 = tmp3;

      tmp1 = R11_old * R13_tmp + R12_old * R23_tmp + R13_old * R33_tmp;
      tmp2 = R21_old * R13_tmp + R22_old * R23_tmp + R23_old * R33_tmp;
      tmp3 = R31_old * R13_tmp + R32_old * R23_tmp + R33_old * R33_tmp;
      R13 = tmp1;
      R23 = tmp2;
      R33 = tmp3;

      double &px_old = input_data[(ind - 1) * size + 2];
      double &py_old = input_data[(ind - 1) * size + 3];
      double &pz_old = input_data[(ind - 1) * size + 4];

      tmp1 = R11 * offset_x + R12 * offset_y + R13 * offset_z + px_old;
      tmp2 = R21 * offset_x + R22 * offset_y + R23 * offset_z + py_old;
      tmp3 = R31 * offset_x + R32 * offset_y + R33 * offset_z + pz_old;

      input_data[ind * size + 2] = tmp1;
      input_data[ind * size + 3] = tmp2;
      input_data[ind * size + 4] = tmp3;


    }

  }

  template<>
  void forward_kinematics_internal(std::array<JointData, 10> &input_data) {
    forward_kinematics_internal_ptr<OP::TRANS, OP::ROT, OP::ROT, OP::ROT, OP::ROT, OP::ROT, OP::ROT, OP::ROT, OP::ROT, OP::ROT>(
        input_data.data()->joint_data.data());
  }

}