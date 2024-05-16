/*********************
 * 
 * 请注意
 * 
 * 本头文件代码应当作为计算程序的接口被调用
 * 
 * 本头文件中包含的内容有：
 *      在 CLI 控制台中打印进度条的成员
 *      打印报错信息所需函数
 *      输出数据所需的函数
 * 
**********************/
# ifndef __HEADER_OUTPUT_H__
# define __HEADER_OUTPUT_H__

# include <direct.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include <unistd.h>

# include "figure.h"
# include "input.h"

namespace CLI_Functions {
    void printError(const char*);
}

namespace processFunctions {
    double process = 1.0;
    bool waitingProcess = false;

    inline void printProcessEnd() {
        waitingProcess = false;
        printf("\033[KDONE");
    }

    /*
    * @brief 打印进度信息
    * @param _p 一个 0~1 的浮点数，表示要打印的进度
    * @note 在进度未到达 100% 时控制台输出组件将处于等待状态，期间不会打印其他信息（除非程序报错退出）
    * @note 在进度到达 100% 时通过调用 printProcess(1.0) 来结束进度等待状态
    */
    void printProcess(const double _p) {
        if (_p == process) return;
        waitingProcess = true;
        process = _p;
        char* str_p = NULL;
        // 为 str_p 动态分配内存空间
        if ((str_p = (char*)malloc(6 * sizeof(char))) == NULL) {
            CLI_Functions::printError("Malloc error!");
        }
        sprintf(str_p, "%.2lf", process * 100);
        printf("\033[K%s%%\033[%dD", str_p, strlen(str_p) + 1);
        free(str_p);
        if (process == 1.0) printProcessEnd();
        return;
    }
}

namespace CLI_Functions {
    /*
    * @brief 打印时间码
    */
    void printTime() {
        puts("\n=================================");
        time_t currentTime;
        time(&currentTime);
        char* timer = ctime(&currentTime);
        timer[strlen(timer) - 1] = '\0';
        printf("[%s]\n", timer);
        return;
    }

    /*
    * @brief 打印报错信息
    * @param _errorMessage 报错信息
    */
    void printError(const char* _errorMessage) {
        printTime();
        printf("ERROR:\n    # ");
        puts(_errorMessage);
        fclose(stdin);
        exit(0);
    }

    /*
    * @brief 打印提示信息
    * @param _noteMessage 提示信息
    */
    void printNote(const char* _noteMessage) {
        if (processFunctions::waitingProcess) return;
        printTime();
        printf("Console : ");
        puts(_noteMessage);
        return;
    }
}

namespace outputFunctions {
    /*
    * @brief 输出计算得分到文件
    * @param 给定输出文件的路径
    */
    void printScores(const char* _path) {
        if (access("./outputfiles/", F_OK) == -1) {
            if (_mkdir("./outputfiles") == -1) 
                CLI_Functions::printError("Creating output directoy failed.");
        }
        CLI_Functions::printNote("Calculating scores.");
        printf("Process : ");
        freopen("outputfiles/Scores.out", "w", stdout);

        printf("Total students number: \t\t%d\n", figureVectors::totNumber);
        printf("Total activities number: \t%d\n", figureVectors::tot.size());
        puts("=============================================================");

        using namespace figureVectors;
        for (int i = 0; i < totNumber; i++) {
            int combo = 0;
            for (int j = 0; j < att[i].size(); j++) {
                if (att[i][j] == 0) {
                    combo = 0;
                    printf("0 ");
                }
                else {
                    combo = combo + 1;
                    printf("%d ", figureFunctions::getScore(combo, tot[j], att[i][j] == 2));
                }
                freopen("CON", "a", stdout);
                processFunctions::printProcess((i * att[i].size() + j + 1.0) / (totNumber * att[i].size()));
                freopen("outputfiles/Scores.out", "a", stdout);
            }
            printf("\n");
        }

        freopen("CON", "a", stdout);
        freopen("CON", "a", stdin);
        CLI_Functions::printNote("Figuring Completed!");
        return;
    }
}

# endif