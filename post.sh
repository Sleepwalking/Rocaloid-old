#!/bin/bash
echo '删除备份文件'
find -regex ".*~"
find -regex ".*~" -delete
echo '清除临时文件'
make -C rsccommon/Debug distclean
echo '输入更新评论'
read commit
git add .
git commit -m "$commit"
echo '更新完成'
