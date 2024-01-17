#include<bits/stdc++.h>
#include <pthread.h>

int n;
int nn[1000];
int ans = 0;

struct hh
{
    int thread_id;
    int start_row;
    int end_row;
};

void *calculate(void *args);

int main(int argc, char *argv[])
{
    int num_threads = strtol(argv[1], NULL, 10);
    pthread_t threads[num_threads];
    struct hh thread_args[num_threads];

    char file_name[10000];
    scanf("%s", file_name);
    if (file_name == NULL)
    {
        return 0;
    }
    FILE *file = fopen(file_name, "r");
    fscanf(file, "%d", &n);
    for (int i = 1; i <= n; i++)
    {
        fscanf(file, "%d", &nn[i]);
    }
    
    nn[0]=1;

    // 使用DP計算最小乘法數
    int dp[n + 1][n + 1];
    memset(dp, 0, sizeof(dp));

    for (int len = 2; len <= n; len++)
    {
        for (int i = 1; i <= n - len + 1; i++)
        {
            int j = i + len - 1;
            dp[i][j] = INT_MAX;

            for (int k = i; k < j; k++)
            {
                int cost = dp[i][k] + dp[k + 1][j] + nn[i - 1] * nn[k] * nn[j];
                if (cost < dp[i][j])
                {
                    dp[i][j] = cost;
                }
            }
        }
    }

    ans = dp[1][n];

    printf("%d", ans);

    fclose(file);

    return 0;
}

void *caculate(void *args)
{
    struct hh *thread_args = (struct hh *)args;
    int thread_id = thread_args->thread_id;
    int start_row = thread_args->start_row;
    int end_row = thread_args->end_row;
    
    int a,b;
    
    for(int i=start_row;i<end_row;i++)
    {
        b=nn[i];
        a=nn[i+1];
        ans+=(a*b);
    }
    
    pthread_exit(NULL);
}
