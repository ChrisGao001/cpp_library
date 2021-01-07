#include <gflags/gflags.h>
#include <functional>
#include <vector>
#include <bthread/bthread.h>
#include <butil/logging.h>

#define logger(text) do { \
    std::cout << text << std::endl; \
} while (0)

DEFINE_int32(thread_num, 2, "thread_num");

namespace util {
    struct RunContext {
        int start;
        int end;
        std::function<void(int,int)> *func;
        RunContext() {
            start = 0;
            end = 0;
            func = nullptr;
        }
    };

    void* handler(void *param) {
        auto ctx = static_cast<RunContext*>(param);
        logger("bid:" << bthread_self() << " run start " << ctx->start << ",end:" << ctx->end);
        (*(ctx->func))(ctx->start, ctx->end);
    }

    void parallel_for(int num_elem, std::function<void(int, int)> func, int num_thread) {
        if (num_elem < 2 * num_thread) {
            func(0, num_elem);
            return;
        }
        int batch_size = num_elem / num_thread;
        logger("batch_size:" << batch_size);
        int res_elem = num_elem % num_thread;
        std::vector<RunContext> params(num_thread);
        std::vector<bthread_t> bids;
        bids.resize(num_thread);
        for (int i=0; i<num_thread; ++i) {
            int start = i * batch_size;
            int end = start + batch_size;
            auto& ctx = params[i];
            ctx.func = &func;
            ctx.start = start;
            ctx.end = end;
            int rc = bthread_start_background(&bids[i], NULL, handler, &ctx);
            logger("create bthread " << bids[i] << ",rc:" << rc);
        }
        if (res_elem > 0) {
            int start = num_elem - res_elem;
            int end = num_elem;
            func(start, end);
            logger("bthread res " << start << ",end:" << end);
        }
        for (const auto& bid : bids) {
            bthread_join(bid, NULL);
            logger("bthread join " << bid);
        }
    }
}

int main(int argc, char** argv) {
    google::ParseCommandLineFlags(&argc, &argv, true);
    logger("begin to run");
    std::vector<int> items(10);
    logger("create function");
    std::function<void(int, int)> func = [&] (int start, int end) {
        while (start < end) {
            items[start] = start * 2;
            logger("bid:" << bthread_self() << " run start " << start << ", end:" << end <<  ",item:" << items[start]);
            ++start;
        }
    };
    util::parallel_for(10, func, FLAGS_thread_num);
    for (auto item : items) {
	logger("item:" << item);
    }
    logger("finish");
    return 0;
}
