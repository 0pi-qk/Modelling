#include <iostream>
#include <fstream>

using namespace std;

int post() {  //интервал поступления
    int k = (rand() % 13) + 1;
    return k;
}

int obr() {  //интервал обработки
    int k = (rand() % 15) + 1;
    return k;
}

int max(int x1, int x2) {  // определение наибольшего числа
    if (x1 > x2) return x1;
    return x2;
}

int main(){
    system("chcp 65001");
    ofstream exel_2_1("2-1.xls");
    exel_2_1 << "Номер шага\tТ инт пост\tТ инт обр\tТ прих\tТ нач обр\tТ ок обр\tТ ож\tТ простоя\t\tНомер шага\tТ инт пост\tТ инт обр\tТ прих\tТ нач обр\tТ ок обр\tТ ож\tТ простоя" << endl;
    ofstream exel_2_2("2-2.xls");
    exel_2_2 << "N\tt зад в оч\tt зад в сист\tP прост ПК\t\tN\tt зад в оч\tt зад в сист\tP прост ПК" << endl;
    int N = 1000;  //количество элементов
    double S_ZS_1 = 0, S_ZO_1 = 0, S_PK_1 = 0, S_ZS_2 = 0, S_ZO_2 = 0, S_PK_2 = 0;
    for (int I = 0; I < 100; I++) {
        //Переменные для первого ПК
        int int_post_1, int_obr_1, prih_1, nach_obr_1, ok_obr_1, ozh_1, prost_1; //таблица
        int pr_prih_1 = 0, pr_1_ok_obr_1 = 0, pr_2_ok_obr_1 = 0;  //для расчетов таблицы
        int Tprost_1 = 0, Tozh_1 = 0, Nozh_1 = 0; double ZS_1, ZO_1, PK_1;  //показатели эффективности СМО
        //Переменные для второго ПК
        int int_post_2, int_obr_2, prih_2, nach_obr_2, ok_obr_2, ozh_2, prost_2; //таблица
        int pr_prih_2 = 0, pr_ok_obr_2 = 0;  //для расчетов таблицы
        int Tprost_2 = 0, Tozh_2 = 0, Nozh_2 = 0; double ZS_2, ZO_2, PK_2;  //показатели эффективности СМО
        for (int i = 1; i <= N; i++) {
            if (i % 2 == 1) {  //первый ПК
                int_post_1 = post();
                int_obr_1 = obr();
                prih_1 = pr_prih_1 + int_post_1;
                nach_obr_1 = max(pr_1_ok_obr_1, prih_1);
                ok_obr_1 = nach_obr_1 + int_obr_1;
                ozh_1 = nach_obr_1 - prih_1;
                prost_1 = nach_obr_1 - pr_1_ok_obr_1;
                if ((i > 2) && (prih_1 <= pr_2_ok_obr_1)) {
                    exel_2_1 << i << "\t" << int_post_1 << "\t" << int_obr_1 << "\t" << "0" << "\t" << "0" << "\t" << "0" << "\t" << "0" << "\t" << "0" << "\t\t";
                    if (i == 999) {
                        ZS_1 = 1. * (ok_obr_1 - Tprost_1) / (N / 2);
                        ZO_1 = 1. * Tozh_1 / Nozh_1;
                        PK_1 = 1. * Tprost_1 / ok_obr_1;
                        S_ZS_1 += ZS_1;
                        S_ZO_1 += ZO_1;
                        S_PK_1 += PK_1;
                        exel_2_2 << I + 1 << "\t" << ZO_1 << "\t" << ZS_1 << "\t" << PK_1 << "\t\t";
                    }
                    continue;
                }
                exel_2_1 << i << "\t" << int_post_1 << "\t" << int_obr_1 << "\t" << prih_1 << "\t" << nach_obr_1 << "\t" << ok_obr_1 << "\t" << ozh_1 << "\t" << prost_1 << "\t\t";
                pr_prih_1 = prih_1;
                pr_2_ok_obr_1 = pr_1_ok_obr_1;
                pr_1_ok_obr_1 = ok_obr_1;
                if (prost_1 != 0)
                    Tprost_1 += prost_1;
                if (ozh_1 != 0) {
                    Tozh_1 += ozh_1;
                    Nozh_1++;
                }
                if (i == 999) {
                    ZS_1 = 1. * (ok_obr_1 - Tprost_1) / (N / 2);
                    ZO_1 = 1. * Tozh_1 / Nozh_1;
                    PK_1 = 1. * Tprost_1 / ok_obr_1;
                    S_ZS_1 += ZS_1;
                    S_ZO_1 += ZO_1;
                    S_PK_1 += PK_1;
                    exel_2_2 << I + 1 << "\t" << ZO_1 << "\t" << ZS_1 << "\t" << PK_1 << "\t\t";
                }
            }
            else {  //второй ПК
                int_post_2 = post();
                int_obr_2 = obr();
                prih_2 = pr_prih_2 + int_post_2;
                nach_obr_2 = max(pr_ok_obr_2, prih_2);
                ok_obr_2 = nach_obr_2 + int_obr_2;
                ozh_2 = nach_obr_2 - prih_2;
                prost_2 = nach_obr_2 - pr_ok_obr_2;
                exel_2_1 << i << "\t" << int_post_2 << "\t" << int_obr_2 << "\t" << prih_2 << "\t" << nach_obr_2 << "\t" << ok_obr_2 << "\t" << ozh_2 << "\t" << prost_2 << endl;
                pr_prih_2 = prih_2;
                pr_ok_obr_2 = ok_obr_2;
                if (prost_2 != 0)
                    Tprost_2 += prost_2;
                if (ozh_2 != 0) {
                    Tozh_2 += ozh_2;
                    Nozh_2++;
                }
                if (i == 1000) {
                    ZS_2 = 1. * (ok_obr_2 - Tprost_2) / (N / 2);
                    ZO_2 = 1. * Tozh_2 / Nozh_2;
                    PK_2 = 1. * Tprost_2 / ok_obr_2;
                    S_ZS_2 += ZS_2;
                    S_ZO_2 += ZO_2;
                    S_PK_2 += PK_2;
                    exel_2_2 << I + 1 << "\t" << ZO_2 << "\t" << ZS_2 << "\t" << PK_2 << endl;
                }
            }
        }
        exel_2_1 << endl;
        if (I == 99) {
            exel_2_2 << endl << endl << "\t" << S_ZO_1 / 100 << "\t" << S_ZS_1 / 100 << "\t" << S_PK_1 / 100 << "\t\t\t" << S_ZO_2 / 100 << "\t" << S_ZS_2 / 100 << "\t" << S_PK_2 / 100;
        }
    }
    cout << "Имитационный эксперимент(1000 элементов) повторенный 100 раз записаны в таблице `Часть 2-1.xls`" << endl
        << "Характеристики работы системы по результатам 100 экспериментов записаны в таблице `Часть 2-2.xls`";
}