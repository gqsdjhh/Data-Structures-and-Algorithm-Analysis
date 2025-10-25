#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <functional>

// 1. 事件总线（核心解耦层）：统一管理事件订阅与发布
class EventBus {
public:
    // 订阅事件：参数1=事件类型，参数2=事件触发时执行的回调
    template <typename EventType>
    void subscribe(const std::string& eventName, std::function<void(EventType)> callback) {
        // 将回调转为通用函数类型，存入对应事件的回调列表
        auto genericCallback = [callback](const void* eventData) {
            callback(*static_cast<const EventType*>(eventData));
        };
        eventCallbacks[eventName].push_back(genericCallback);
    }

    // 发布事件：参数1=事件类型，参数2=事件数据
    template <typename EventType>
    void publish(const std::string& eventName, const EventType& eventData) {
        // 找到该事件的所有回调，依次执行
        if (eventCallbacks.find(eventName) != eventCallbacks.end()) {
            for (auto& callback : eventCallbacks[eventName]) {
                callback(&eventData); // 传入事件数据地址
            }
        }
    }

private:
    // 存储事件回调：key=事件名，value=通用回调函数列表
    using GenericCallback = std::function<void(const void*)>;
    std::unordered_map<std::string, std::vector<GenericCallback>> eventCallbacks;
};

// 2. 定义事件数据（代替原有的直接传字符串，更规范）
struct ArticleEvent {
    std::string publisher; // 发布者（如"技术公众号"）
    std::string title;     // 文章标题
    std::string content;   // 文章内容
};

// 3. 被观察者（公众号）：仅依赖EventBus，无需知道任何观察者
class TechWechat {
public:
    TechWechat(EventBus& bus) : eventBus(bus) {} // 构造时注入事件总线

    // 发布文章：向总线发布"article_published"事件
    void publishArticle(const std::string& title) {
        ArticleEvent event;
        event.publisher = "技术公众号";
        event.title = title;
        event.content = "[技术干货] " + title;

        std::cout << "\n" << event.publisher << "发布新文章：" << event.title << std::endl;
        eventBus.publish("article_published", event); // 仅与总线交互
    }

private:
    EventBus& eventBus; // 依赖事件总线（而非观察者列表）
};

// 4. 观察者（用户）：仅依赖EventBus和事件数据，无需知道公众号
class User {
public:
    User(EventBus& bus, const std::string& name) : eventBus(bus), userName(name) {
        // 订阅"article_published"事件，定义回调逻辑
        eventBus.subscribe<ArticleEvent>("article_published", 
            [this](const ArticleEvent& event) {
                std::cout << userName << "收到通知：【" << event.publisher << "】的《" 
                          << event.title << "》→ " << getAction() << std::endl;
            }
        );
    }

private:
    // 不同用户的差异化行为（模拟个性化响应）
    std::string getAction() const {
        if (userName == "用户A") return "立即阅读";
        if (userName == "用户B") return "收藏备用";
        return "标记稍后看";
    }

    EventBus& eventBus;
    std::string userName;
};

// 主函数：测试解耦逻辑
int main() {
    // 1. 创建全局事件总线
    EventBus globalBus;

    // 2. 创建观察者（用户）：仅需总线，无需知道公众号
    User userA(globalBus, "用户A");
    User userB(globalBus, "用户B");
    User userC(globalBus, "用户C"); // 新增用户无需修改公众号代码

    // 3. 创建被观察者（公众号）：仅需总线，无需知道用户
    TechWechat techWechat(globalBus);

    // 4. 公众号发布文章：自动通知所有订阅者
    techWechat.publishArticle("C++ 事件总线设计");
    techWechat.publishArticle("STL 高效使用技巧");

    return 0;
}