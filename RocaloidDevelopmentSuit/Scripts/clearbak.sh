#!/bin/bash
echo "删除所有编辑后剩下的'~'文件中"
echo "文件列表："
find -regex ".*~"
find -regex ".*~" -delete
echo "删除成功，按任意键结束"
read
