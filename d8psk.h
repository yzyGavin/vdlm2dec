/*
 *  Copyright (c) 2016 Thierry Leconte
 *
 *   
 *   This code is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU Library General Public License version 2
 *   published by the Free Software Foundation.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU Library General Public License for more details.
 *
 *   You should have received a copy of the GNU Library General Public
 *   License along with this library; if not, write to the Free Software
 *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

static const float SW[NBPH] = {
    2 * M_PI / 8, 3 * M_PI / 8, 10 * M_PI / 8, 15 * M_PI / 8,
    8 * M_PI / 8, 9 * M_PI / 8, 12 * M_PI / 8, 9 * M_PI / 8,
    2 * M_PI / 8, 5 * M_PI / 8, 4 * M_PI / 8, 9 * M_PI / 8,
    4 * M_PI / 8, M_PI / 8, -4 * M_PI / 8, -5 * M_PI / 8,
    2 * M_PI / 8
};

static const float mflt[9][MFLTLEN] = {
    {0.0067657, -0.0147744, -0.0643762, -0.1058691, -0.0687838, 0.1065617, 0.4115732, 0.7477373, 0.9693810, 0.9693810,
     0.7477373, 0.4115732, 0.1065617, -0.0687838, -0.1058691, -0.0643762, -0.0147744},
    {0.0057574, -0.0197402, -0.0712362, -0.1071089, -0.0551075, 0.1387967, 0.4547334, 0.7846463, 0.9826931, 0.9524552,
     0.7089863, 0.3689687, 0.0764806, -0.0802056, -0.1033906, -0.0574414, -0.0103039},
    {0.0043135, -0.0251716, -0.0778990, -0.1069540, -0.0391115, 0.1730641, 0.4981679, 0.8194268, 0.9922813, 0.9320548,
     0.6686901, 0.3271881, 0.0486498, -0.0894564, -0.0998311, -0.0505439, -0.0063475},
    {0.0024028, -0.0310270, -0.0842330, -0.1052527, -0.0207503, 0.2092180, 0.5415839, 0.8518054, 0.9980663, 0.9083470,
     0.6271523, 0.2864833, 0.0231408, -0.0966361, -0.0953485, -0.0437846, -0.0029133},
    {0, -3.7253e-02, -9.0098e-02, -1.0186e-01, 2.7377e-17, 2.4709e-01, 5.8468e-01, 8.8152e-01, 1.0000e+00, 8.8152e-01,
     5.8468e-01, 2.4709e-01, 2.7377e-17, -1.0186e-01, -9.0098e-02, -3.7253e-02, 0},
    {-0.0029133, -0.0437846, -0.0953485, -0.0966361, 0.0231408, 0.2864833, 0.6271523, 0.9083470, 0.9980663, 0.8518054,
     0.5415839, 0.2092180, -0.0207503, -0.1052527, -0.0842330, -0.0310270, 0.0024028},
    {0.0063475, -0.0505439, -0.0998311, -0.0894564, 0.0486498, 0.3271881, 0.6686901, 0.9320548, 0.9922813, 0.8194268,
     0.4981679, 0.1730641, -0.0391115, -0.1069540, -0.0778990, -0.0251716, 0.0043135},
    {-0.0103039, -0.0574414, -0.1033906, -0.0802056, 0.0764806, 0.3689687, 0.7089863, 0.9524552, 0.9826931, 0.7846463,
     0.4547334, 0.1387967, -0.0551075, -0.1071089, -0.0712362, -0.0197402, 0.0057574},
    {-0.0147744, -0.0643762, -0.1058691, -0.0687838, 0.1065617, 0.4115732, 0.7477373, 0.9693810, 0.9693810, 0.7477373,
     0.4115732, 0.1065617, -0.0687838, -0.1058691, -0.0643762, -0.0147744, 0.0067657}
};

static const float Grey1[257] = {
    0.500000,
    0.547114, 0.593379, 0.638007, 0.680323, 0.719801, 0.756080, 0.788964, 0.818405,
    0.844475, 0.867341, 0.887234, 0.904421, 0.919182, 0.931801, 0.942548, 0.951672,
    0.959400, 0.965936, 0.971456, 0.976114, 0.980044, 0.983359, 0.986153, 0.988508,
    0.990492, 0.992162, 0.993565, 0.994741, 0.995724, 0.996542, 0.997220, 0.997777,
    0.998233, 0.998604, 0.998902, 0.999140, 0.999330, 0.999479, 0.999596, 0.999687,
    0.999758, 0.999813, 0.999856, 0.999888, 0.999913, 0.999933, 0.999947, 0.999959,
    0.999968, 0.999975, 0.999980, 0.999984, 0.999987, 0.999990, 0.999992, 0.999994,
    0.999995, 0.999996, 0.999996, 0.999997, 0.999997, 0.999998, 0.999998, 0.999998,
    0.999998, 0.999998, 0.999997, 0.999997, 0.999996, 0.999996, 0.999995, 0.999994,
    0.999992, 0.999990, 0.999987, 0.999984, 0.999980, 0.999975, 0.999968, 0.999959,
    0.999947, 0.999933, 0.999913, 0.999888, 0.999856, 0.999813, 0.999758, 0.999687,
    0.999596, 0.999479, 0.999330, 0.999140, 0.998902, 0.998604, 0.998233, 0.997777,
    0.997220, 0.996542, 0.995724, 0.994741, 0.993565, 0.992162, 0.990492, 0.988508,
    0.986153, 0.983359, 0.980044, 0.976114, 0.971456, 0.965936, 0.959400, 0.951672,
    0.942548, 0.931801, 0.919182, 0.904421, 0.887234, 0.867341, 0.844475, 0.818405,
    0.788964, 0.756080, 0.719801, 0.680323, 0.638007, 0.593379, 0.547114, 0.500000,
    0.452886, 0.406621, 0.361993, 0.319677, 0.280199, 0.243920, 0.211036, 0.181595,
    0.155525, 0.132659, 0.112766, 0.095579, 0.080818, 0.068199, 0.057452, 0.048328,
    0.040600, 0.034064, 0.028544, 0.023886, 0.019956, 0.016641, 0.013847, 0.011492,
    0.009508, 0.007838, 0.006435, 0.005259, 0.004276, 0.003458, 0.002780, 0.002223,
    0.001767, 0.001396, 0.001098, 0.000860, 0.000670, 0.000521, 0.000404, 0.000313,
    0.000242, 0.000187, 0.000144, 0.000112, 0.000087, 0.000067, 0.000053, 0.000041,
    0.000032, 0.000025, 0.000020, 0.000016, 0.000013, 0.000010, 0.000008, 0.000006,
    0.000005, 0.000004, 0.000004, 0.000003, 0.000003, 0.000002, 0.000002, 0.000002,
    0.000002, 0.000002, 0.000003, 0.000003, 0.000004, 0.000004, 0.000005, 0.000006,
    0.000008, 0.000010, 0.000013, 0.000016, 0.000020, 0.000025, 0.000032, 0.000041,
    0.000053, 0.000067, 0.000087, 0.000112, 0.000144, 0.000187, 0.000242, 0.000313,
    0.000404, 0.000521, 0.000670, 0.000860, 0.001098, 0.001396, 0.001767, 0.002223,
    0.002780, 0.003458, 0.004276, 0.005259, 0.006435, 0.007838, 0.009508, 0.011492,
    0.013847, 0.016641, 0.019956, 0.023886, 0.028544, 0.034064, 0.040600, 0.048328,
    0.057452, 0.068199, 0.080818, 0.095579, 0.112766, 0.132659, 0.155525, 0.181595,
    0.211036, 0.243920, 0.280199, 0.319677, 0.361993, 0.406621, 0.452886, 0.500000
};

static const float Grey2[257] = {
    0.999998,
    0.999998, 0.999998, 0.999997, 0.999997, 0.999996, 0.999996, 0.999995, 0.999994,
    0.999992, 0.999990, 0.999987, 0.999984, 0.999980, 0.999975, 0.999968, 0.999959,
    0.999947, 0.999933, 0.999913, 0.999888, 0.999856, 0.999813, 0.999758, 0.999687,
    0.999596, 0.999479, 0.999330, 0.999140, 0.998902, 0.998604, 0.998233, 0.997777,
    0.997220, 0.996542, 0.995724, 0.994741, 0.993565, 0.992162, 0.990492, 0.988508,
    0.986153, 0.983359, 0.980044, 0.976114, 0.971456, 0.965936, 0.959400, 0.951672,
    0.942548, 0.931801, 0.919182, 0.904421, 0.887234, 0.867341, 0.844475, 0.818405,
    0.788964, 0.756080, 0.719801, 0.680323, 0.638007, 0.593379, 0.547114, 0.500000,
    0.452886, 0.406621, 0.361993, 0.319677, 0.280199, 0.243920, 0.211036, 0.181595,
    0.155525, 0.132659, 0.112766, 0.095579, 0.080818, 0.068199, 0.057452, 0.048328,
    0.040600, 0.034064, 0.028544, 0.023886, 0.019956, 0.016641, 0.013847, 0.011492,
    0.009508, 0.007838, 0.006435, 0.005259, 0.004276, 0.003458, 0.002780, 0.002223,
    0.001767, 0.001396, 0.001098, 0.000860, 0.000670, 0.000521, 0.000404, 0.000313,
    0.000242, 0.000187, 0.000144, 0.000112, 0.000087, 0.000067, 0.000053, 0.000041,
    0.000032, 0.000025, 0.000020, 0.000016, 0.000013, 0.000010, 0.000008, 0.000006,
    0.000005, 0.000004, 0.000004, 0.000003, 0.000003, 0.000002, 0.000002, 0.000002,
    0.000002, 0.000002, 0.000003, 0.000003, 0.000004, 0.000004, 0.000005, 0.000006,
    0.000008, 0.000010, 0.000013, 0.000016, 0.000020, 0.000025, 0.000032, 0.000041,
    0.000053, 0.000067, 0.000087, 0.000112, 0.000144, 0.000187, 0.000242, 0.000313,
    0.000404, 0.000521, 0.000670, 0.000860, 0.001098, 0.001396, 0.001767, 0.002223,
    0.002780, 0.003458, 0.004276, 0.005259, 0.006435, 0.007838, 0.009508, 0.011492,
    0.013847, 0.016641, 0.019956, 0.023886, 0.028544, 0.034064, 0.040600, 0.048328,
    0.057452, 0.068199, 0.080818, 0.095579, 0.112766, 0.132659, 0.155525, 0.181595,
    0.211036, 0.243920, 0.280199, 0.319677, 0.361993, 0.406621, 0.452886, 0.500000,
    0.547114, 0.593379, 0.638007, 0.680323, 0.719801, 0.756080, 0.788964, 0.818405,
    0.844475, 0.867341, 0.887234, 0.904421, 0.919182, 0.931801, 0.942548, 0.951672,
    0.959400, 0.965936, 0.971456, 0.976114, 0.980044, 0.983359, 0.986153, 0.988508,
    0.990492, 0.992162, 0.993565, 0.994741, 0.995724, 0.996542, 0.997220, 0.997777,
    0.998233, 0.998604, 0.998902, 0.999140, 0.999330, 0.999479, 0.999596, 0.999687,
    0.999758, 0.999813, 0.999856, 0.999888, 0.999913, 0.999933, 0.999947, 0.999959,
    0.999968, 0.999975, 0.999980, 0.999984, 0.999987, 0.999990, 0.999992, 0.999994,
    0.999995, 0.999996, 0.999996, 0.999997, 0.999997, 0.999998, 0.999998, 0.999998
};

static const float Grey3[257] = {
    0.004445,
    0.004547, 0.004854, 0.005374, 0.006118, 0.007105, 0.008359, 0.009911, 0.011804,
    0.014088, 0.016828, 0.020100, 0.023997, 0.028631, 0.034132, 0.040652, 0.048369,
    0.057484, 0.068224, 0.080838, 0.095595, 0.112778, 0.132668, 0.155533, 0.181602,
    0.211040, 0.243923, 0.280202, 0.319679, 0.361994, 0.406622, 0.452887, 0.500000,
    0.547113, 0.593378, 0.638006, 0.680321, 0.719798, 0.756077, 0.788960, 0.818398,
    0.844467, 0.867332, 0.887222, 0.904405, 0.919162, 0.931776, 0.942516, 0.951631,
    0.959348, 0.965868, 0.971369, 0.976003, 0.979900, 0.983172, 0.985912, 0.988196,
    0.990089, 0.991641, 0.992895, 0.993882, 0.994626, 0.995146, 0.995453, 0.995555,
    0.995453, 0.995146, 0.994626, 0.993882, 0.992895, 0.991641, 0.990089, 0.988196,
    0.985912, 0.983172, 0.979900, 0.976003, 0.971369, 0.965868, 0.959348, 0.951631,
    0.942516, 0.931776, 0.919162, 0.904405, 0.887222, 0.867332, 0.844467, 0.818398,
    0.788960, 0.756077, 0.719798, 0.680321, 0.638006, 0.593378, 0.547113, 0.500000,
    0.452887, 0.406622, 0.361994, 0.319679, 0.280202, 0.243923, 0.211040, 0.181602,
    0.155533, 0.132668, 0.112778, 0.095595, 0.080838, 0.068224, 0.057484, 0.048369,
    0.040652, 0.034132, 0.028631, 0.023997, 0.020100, 0.016828, 0.014088, 0.011804,
    0.009911, 0.008359, 0.007105, 0.006118, 0.005374, 0.004854, 0.004547, 0.004445,
    0.004547, 0.004854, 0.005374, 0.006118, 0.007105, 0.008359, 0.009911, 0.011804,
    0.014088, 0.016828, 0.020100, 0.023997, 0.028631, 0.034132, 0.040652, 0.048369,
    0.057484, 0.068224, 0.080838, 0.095595, 0.112778, 0.132668, 0.155533, 0.181602,
    0.211040, 0.243923, 0.280202, 0.319679, 0.361994, 0.406622, 0.452887, 0.500000,
    0.547113, 0.593378, 0.638006, 0.680321, 0.719798, 0.756077, 0.788960, 0.818398,
    0.844467, 0.867332, 0.887222, 0.904405, 0.919162, 0.931776, 0.942516, 0.951631,
    0.959348, 0.965868, 0.971369, 0.976003, 0.979900, 0.983172, 0.985912, 0.988196,
    0.990089, 0.991641, 0.992895, 0.993882, 0.994626, 0.995146, 0.995453, 0.995555,
    0.995453, 0.995146, 0.994626, 0.993882, 0.992895, 0.991641, 0.990089, 0.988196,
    0.985912, 0.983172, 0.979900, 0.976003, 0.971369, 0.965868, 0.959348, 0.951631,
    0.942516, 0.931776, 0.919162, 0.904405, 0.887222, 0.867332, 0.844467, 0.818398,
    0.788960, 0.756077, 0.719798, 0.680321, 0.638006, 0.593378, 0.547113, 0.500000,
    0.452887, 0.406622, 0.361994, 0.319679, 0.280202, 0.243923, 0.211040, 0.181602,
    0.155533, 0.132668, 0.112778, 0.095595, 0.080838, 0.068224, 0.057484, 0.048369,
    0.040652, 0.034132, 0.028631, 0.023997, 0.020100, 0.016828, 0.014088, 0.011804,
    0.009911, 0.008359, 0.007105, 0.006118, 0.005374, 0.004854, 0.004547, 0.004445
};