#ifndef TOOLS_TIMER_H
#define TOOLS_TIMER_H

#include <chrono>
using namespace std::chrono;
using std::chrono::duration_cast;
typedef std::chrono::high_resolution_clock high_clock;

namespace belien {

/**
 * @brief 计时器
 */
class ToolsTimer {
private:
    time_point< high_clock > m_begin; // 开始时间

public:
    ToolsTimer() : m_begin(high_clock::now()) {}
    ~ToolsTimer() {}

    /**
     * @brief  重置当前计时
     */
    void reset() {
        m_begin = high_resolution_clock::now();
    }

public:
    /**
     * @brief  Get the Milli Seconds object
     * @return int64_t : 毫秒
     */
    int64_t getMilliSeconds() const {
        return duration_cast< milliseconds >(high_clock::now() - m_begin)
            .count();
    }

    /**
     * @brief  Get the Seconds object
     * @return double : 秒
     */
    double getSeconds() const {
        return duration_cast< duration< double > >(high_clock::now() - m_begin)
            .count();
    }

    /**
     * @brief  Get the Micro Seconds object
     * @return int64_t : 微妙
     */
    int64_t getMicroSeconds() const {
        return duration_cast< microseconds >(high_clock::now() - m_begin)
            .count();
    }

    /**
     * @brief  Get the Nano Seconds object
     * @return int64_t : 纳秒
     */
    int64_t getNanoSeconds() const {
        return duration_cast< nanoseconds >(high_clock::now() - m_begin)
            .count();
    }

    /**
     * @brief  Get the Minutes object
     * @return int64_t : 分钟
     */
    int64_t getMinutes() const {
        return duration_cast< minutes >(high_resolution_clock::now() - m_begin)
            .count();
    }

    /**
     * @brief  Get the Hours object
     * @return int64_t : 小时
     */
    int64_t getHours() const {
        return duration_cast< hours >(high_resolution_clock::now() - m_begin)
            .count();
    }
};
} // namespace belien

#endif
