/*********************
 * 
 * 请注意
 * 
 * 本头文件代码应当作为计算程序的接口被调用
 * 
 * 本头文件中包含的内容有：
 *      计算过程中用到的常量
 *      计算过程中使用的向量
 *      计算过程中需要的函数
 * 
**********************/
# ifndef __HEADER_FIGURE_H__
# define __HEADER_FIGURE_H__

# include <vector>
# include <cmath>

namespace figureConsts {
    const double LOG_TIME = 15.0;               // 计算公式中对数的系数
    const double LOG_BASE = 10.0;               // 计算公式中使用的对数底
    const double SCR_TOTL = 100.0;              // 计算公式中的基础总分
    const double SCR_RATE = 0.25;               // 计算公式中的倍率增长率
    const double SCR_XTRA = 5.0;                // 计算公式中的额外得分
}

namespace figureVectors {
    int totNumber;                              // 班级总学生数（用于进行性能预估）
    std::vector<std::vector<int>> att;          // 学生活动记录矩阵
    std::vector<int> tot;                       // 每次活动应到人数
}

namespace figureFunctions {
    using namespace figureConsts;

    /*
    * @brief 根据学生活动记录矩阵计算单个学生的连续参与数向量
    * @param _recordVec 学生活动记录矩阵中的一行，函数会根据给定的这一行计算连续参与数
    * @param _comboVec 用于存储输出信息的向量，函数会在其中填入计算出的连续参与数信息
    */
    void getCombo(std::vector<int>& _recordVec, std::vector<int>& _comboVec) {
        int temp = 0;
        _comboVec.clear();
        for (int i : _recordVec) {
            if (i != 0) temp++;
            else temp = 0;
            _comboVec.push_back(temp);
        }
        return;
    }

    /*
    * @brief 计算给定真数在给定底数下的对数
    * @param _n 给定的真数
    * @param _b 给定的底数
    */
    double getLog(double _n, double _b) {
        return std::log(_n) / std::log(_b);
    }

    /*
    * @brief 计算单次活动得分
    * @param _combo 连续参与次数
    * @param _tot   活动应到人数
    * @param _extra 是否特殊贡献
    * @return 给定参数对应数据的单个单元格的积分
    */
    int getScore(int _combo, int _tot, bool _extra) {
        return int(LOG_TIME * getLog(SCR_TOTL / _tot * (1 + SCR_RATE * (_combo - 1)), LOG_BASE)) + (int)_extra * SCR_XTRA;
    }
}

# endif