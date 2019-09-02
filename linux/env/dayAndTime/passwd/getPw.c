#include <pwd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "ourhdr.h"

int main(){
        struct passwd *pw;
        uid_t uid = getuid();
        gid_t gid = getgid();

        printf("User is %s\n",getlogin());
        printf("User IDs : uid = %d, gid = %d\n",uid,gid);

        pw = getpwuid(uid);
        printf("UID passwd entry:\n password=%s name=%s, uid=%d, gid=%d, home=%s, shell=%s\n",
                        pw->pw_passwd,pw->pw_name,pw->pw_uid,pw->pw_gid,pw->pw_dir,pw->pw_shell);
        exit(0);
}
