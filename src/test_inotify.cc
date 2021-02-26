#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/unistd.h>
#include <sys/inotify.h>

int main()
{
    int notify_fd = inotify_init();
    inotify_add_watch(notify_fd, "tt.cc", IN_MODIFY | IN_CREATE | IN_DELETE);

    static const uint32_t BUFFSIZE = 10240;
    char buf[BUFFSIZE + 1] = {0};
    while (true)
    {
        uint32_t read_num = read(notify_fd, buf, BUFFSIZE);
        if (read_num == 0) {
            continue;
        } else {
            uint32_t i = 0;
            while (i < read_num)
            {
                struct inotify_event* event = (struct inotify_event*)&buf[i];
                std::cout << event->len << std::endl;
                struct stat st;
                fstat(event->wd, &st);
                std::cout << event->len << std::endl;
                i += sizeof(struct inotify_event);
            }
           
            
            
        }
    }
    return 0;
    
}