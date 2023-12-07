# TODO: Make this pretty

3 dependencies -> 3 env variabiles containins their library path

KQLOG_LIBRARY_PATH=\<path to kqlog\>  
KQNET_LIBRARY_PATH=\<path to kqnet\>  
IMGUI_LIBRARY_PATH=\<path to imgui\>  

# How to:

Open a `cmd.exe` as `administrator` and run the following:

```
setx /m KQLOG_LIBRARY_PATH <path to kqlog>  
setx /m KQNET_LIBRARY_PATH <path to kqnet>  
setx /m IMGUI_LIBRARY_PATH <path to imgui> 
```