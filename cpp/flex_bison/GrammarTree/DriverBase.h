// Driver当中持有所有的节点内存对象，该类设计的一个缺陷是节点的生存周期
// 必须与Driver的生存周期相同
#ifndef __DriverBase_H__
#define __DriverBase_H__

#include <string>
#include <map>

#include <glog/logging.h>

#include "Node.h"

namespace BA {

class DriverBase
{
public:
    DriverBase ()
    {
    }

    virtual ~DriverBase ()
    {
        ReleaseNode();
    }

    /*
     * 将节点保存在节点列表当中，方便集中管理内存
     */
    void BackupNode(BA::Node* node)
    {
        _nodes.push_back(node);
    }

    //释放所有节点
    void ReleaseNode(void)
    {
        for (std::vector<BA::Node*>::size_type i = 0;
            i < _nodes.size();
            i++)
        {
            delete _nodes[i];
            _nodes[i] = NULL;
        }

        /*
        LOG(INFO) << "DriverBase released node total:" << _nodes.size();
        */

        _nodes.clear();
    }

private:

    //保存申请的所有的内存，方便管理
    std::vector<BA::Node*> _nodes;
};

} /*namespace BA*/

#endif /*!__DriverBase_H__*/
