/*********************
 * 
 * 请注意
 * 
 * 本头文件代码应当作为计算程序的接口被调用
 * 
 * 本头文件中包含的内容有：
 *      输入数据所需的函数
 * 
**********************/
# ifndef __HEADER_INPUT_H__
# define __HEADER_INPUT_H__

# include <stdio.h>

# include "figure.h"
# include "output.h"

namespace inputFunctions {
    FILE* inputFileHandle;

    inline bool isDigit(const char& _ch) { return _ch >= '0' && _ch <= '9'; }
    inline int getDigit(const char& _ch) { return _ch - '0'; }

    // 读取一行数据
    std::vector<int> getLineData() {
        std::vector<int> rst;
        char _ch = getchar();
        while (_ch == '\n') _ch = getchar();            // 过滤行末换行
        while (true) {
            int _data = 0;
            while (_ch == ' ') _ch = getchar();         // 过滤空格
            while (isDigit(_ch)) {
                _data = _data * 10 + getDigit(_ch);
                _ch = getchar();
            }
            if (_ch != ' ') {
                if (_ch == '\n' || _ch == EOF) break;   // 除空格、换行和数字外的字符均为非法字符
                else CLI_Functions::printError("Invalid character.");
            }
            else _ch = getchar();
            rst.push_back(_data);
        }
        return rst;
    }

    // 检查应到人数向量是否合法
    // 合法性检验：应到人数应是在区间 [1, n] 内的整数
    inline bool checkVector() {
        for (int i : figureVectors::tot) 
            if (i < 1 || i > figureVectors::totNumber) return false;
        return true;
    }

    // 检查矩阵列数是否一致
    // @param _ind 要检查的行编号
    inline void checkMatrix(std::vector<int>& _lne) {
        using namespace figureVectors;
        if (_lne.size() != tot.size()) CLI_Functions::printError("Invalid matrix.");
        for (int i : _lne) {
            if (i < 0 || i > 2) CLI_Functions::printError("Invalid element in matrix.");
        }
        return;
    }

    // 读取班级总人数
    void getNumber() {
        figureVectors::totNumber = getLineData()[0];
        return;
    }

    // 读取活动人数记录向量
    void getVector() {
        using namespace figureVectors;
        tot = getLineData();

        if (!checkVector()) {
            CLI_Functions::printError("Invalid element in vector.");
        } 
        else if (tot.size() * totNumber > 1e6) {
            CLI_Functions::printNote("The volumn of input was too large.");
        }
        else {
            CLI_Functions::printNote("Vector scaned.");
        }

        return;
    }
    // 读取学生活动记录矩阵
    void getMatrix() {
        CLI_Functions::printNote("Scanning matrix.");
        printf("Process : ");
        processFunctions::printProcess(0.0);

        using namespace figureVectors;
        for (int i = 0; i < totNumber; i++) {
            att.push_back({});
            att[i] = getLineData();
            checkMatrix(att[i]);
            processFunctions::printProcess((i + 1.0) / totNumber);
        }

        processFunctions::printProcess(1.0);
        CLI_Functions::printNote("Matrix scanned.");
        return;
    }

    /*
    * @brief 从文件读取数据
    * @param 给定输入文件的路径
    */
    void inputFile(const char* _filePath) {
        inputFileHandle = freopen(_filePath, "r", stdin);

        if (inputFileHandle == NULL) {
            CLI_Functions::printError("Could not find file.");
        } else {
            CLI_Functions::printNote("File opened.");
        }

        getNumber();
        getVector();
        getMatrix();

        fclose(inputFileHandle);
        return;
    }

}

# endif