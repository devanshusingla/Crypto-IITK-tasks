### Assumptions to use this example.

1. cloning directory of grpc is in /home/devanshu/softwares/git/grpc.
   **_NOTE: here grpc is outer folder and contains the main grpc folder_**
   Replace its occurence in Makefile with your cloning directory

2. task is the name of the file with .proto extension. Replace occurrence of task with name in your proto extension.

3. add this in your ~/.bashrc

```
export PKG_CONFIG_PATH=/home/devanshu/softwares/git/grpc/lib/pkgconfig
```

**_NOTE: Again replace with your directory with cloned gprc_**

4. in Makefile add the path of your proto file like task.proto in PROTOS_PATH.
