#!/bin/bash
if [[ $# -lt 2 ]];then
	echo "usage:`basename $0` v7.2.3 <commit_id>"
	exit 1
fi

branch=$1
commit_ids=$@
erp="gaoyumin1"

if [[ -d searcher ]];then
    \rm -rf searcher
fi

git clone ssh://${erp}@gerrit.jd.com:443/jd_search/searcher
cd searcher

git checkout --track origin/$branch
for commit_id in $commit_ids;do
	echo "begin to pick $commit_id"
	git cherry-pick $commit_id
done

git push ssh://${erp}@gerrit.jd.com:443/jd_search/searcher ${branch}:refs/for/${branch}
