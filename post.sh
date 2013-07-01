#!/bin/bash
echo '删除备份文件'
find -regex ".*~"
find -regex ".*~" -delete
echo '清除临时文件'
#make -C cyberengine/Debug distclean
#rm -rf cyberengine/autom4te.cache
echo '输入更新评论'
read commit
git add .
git commit -m "$commit"
git push
echo '更新完成'
