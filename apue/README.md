
### 准备工作

- apue.h 缺失
```markdown
download
notes/apue/res/src.3e.tar.gz     
tar -xzvf src.3e.tar.gz

cp ./apue.3e/include/apue.h /usr/include/
cp ./apue.3e/lib/error.c /usr/include/

编辑/usr/include/apue.h文件
在文件最后#endif前加上包含error.c的代码：
#include "error.c";
```