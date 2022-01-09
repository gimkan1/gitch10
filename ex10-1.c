#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/signal.h>

void handler(int signum);
int flag = 5;

    // 태그 버전 실습 파일입니다.
        // 버전 1.0.0 실습
        // 버전 1.1.0 실습
            // 수정작업 1.1.1 실습
            // 수정작업 1.1.2 실습
        // 버전 2.0.0 lightweight 실습

int main()
{
    struct sigaction act;
    sigset_t set;

    sigemptyset(&(act.sa_mask));
    sigaddset(&(act.sa_mask), SIGALRM);
    sigaddset(&(act.sa_mask), SIGINT);
    sigaddset(&(act.sa_mask), SIGUSR1);

    act.sa_handler = handler; 
    sigaction(SIGALRM, &act, NULL);
    sigaction(SIGINT, &act, NULL);
    sigaction(SIGUSR1, &act, NULL);

    printf("call raise(SIGUSR1) before blocking\n");
    raise(SIGUSR1);

    sigemptyset(&set);
    sigaddset(&set, SIGUSR1);
    sigprocmask(SIG_SETMASK, &set, NULL);

    while (flag)
    {
        printf("input SIGINT [%d]\n", flag);
        sleep(1);
    }

    printf("call kill(getpid(), SIGUSR1) after blocking\n");
    kill(getpid(), SIGUSR1);

    printf("sleep by pause.. zzZZ\n");
    printf("pause return %d\n", pause());

    printf("2 seconds sleeping..zzZZ\n");
    alarm(2);
    pause();

    return 0;
}

void handler(int signum)
{
    flag--;

    switch(signum){
        case SIGINT:
            printf("SIGING(%d)\n", signum);
            break;
        case SIGALRM:
            printf("SIGALRM(%d)\n", signum);
            break;
        case SIGUSR1:
            printf("SIGUSR1(%d)\n", signum);
            break;
        default:
            printf("signal(%d)\n", signum);
    }
}