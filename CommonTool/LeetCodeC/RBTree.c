//
//  RBTree.c
//  CommonTool
//
//  Created by lizihong on 2023/1/13.
//  Copyright © 2023 AL. All rights reserved.
//


// 红黑树实现
#include "RBTree.h"

#include<iostream>
#include<stdlib.h>
#include<string.h>
#define red 0
#define black 1
using namespace std;

struct node//节点的结构
{
    int data;
    char color;
    struct node* parent;
    struct node* left;
    struct node* right;
};
struct Tree//树的结构
{
    struct node* root;
};
//创建一个节点
struct node* Creat_Node(int data, int color, struct node* left, struct node* right, struct node* parent)
{
    struct node* New = malloc(sizeof(struct node));
    New->data = data;
    New->color = color;
    New->left = left;
    New->right = right;
    New->parent = parent;
    return New;
}

/*
 * 左旋示意图(对节点x进行左旋)：
 *
 *
 *      px                              px
 *     /                               /
 *    x                               y
 *   /        --(左旋)-->           /                 #
 *  lx   y                          x  ry
 *     /                          /
 *    ly   ry                     lx  ly
 *
 * 三处变化：
 * 1、被旋转的节点  变成  左节点
 * 2、被旋转节点的右节点  变成  根节点
 * 3、被旋转节点的右节点的左节点  变成  被旋转节点的右节点
 *
 * 代码实现的时候，修改这种变化从第3点开始修改（也就是最下面的变化开始往上修改）
 */

 //以x为支点进行左旋
void LeftRotate(Tree* tree, node* x)
{
    //新建节点y,保存x的右节点
    node* y = x->right;

    //将被旋转节点的右节点的左节点  设置为  被旋转节点的右节点
    x->right = y->left;

    //更新被旋转节点x的  右节点的左节点  的父节点
    if (y->left != NULL)
        y->left->parent = x;

    //更新旋转后  y的父节点
    y->parent = x->parent;

    //判断x为根节点的情况，那么旋转后y变成根节点
    if (x->parent == NULL)
        tree->root = y;
    else
    {
        //如果x是它父节点的左儿子，旋转后这个父节点的左儿子就是y
        if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
    }

    y->left = x;
    x->parent = y;

}

/*
 * 右旋示意图(对节点y进行左旋)：
 *
 *
 *            py                               py
 *           /                                /
 *          y                                x
 *         /        --(右旋)-->            /                       #
 *        x   ry                           lx   y
 *       /                                    /                    #
 *      lx  rx                                rx  ry
 *
 * 三处变化：
 * 1、被旋转的节点  变成  右节点
 * 2、被旋转节点的左节点  变成  根节点
 * 3、被旋转节点的左节点的右节点  变成  被旋转节点的左节点
 */

 //以y为支点进行左旋
void RightRotate(Tree* tree, node* y)
{
    //新建x节点保存被旋转节点的左节点
    node* x = y->left;

    //将被旋转节点的左节点的右节点  设置为  被旋转节点的左节点
    y->left = x->right;

    //更新被旋转节点y的  左节点的右节点  的父节点
    if (x->right != NULL)
        x->right->parent = y;

    //更新旋转后  x的父节点
    x->parent = y->parent;

    //判断y为根节点的情况，那么旋转后x变成根节点
    if (y->parent == NULL)
        tree->root = x;
    else
    {
        //如果被旋转节点y是它父节点的左儿子，旋转后这个父节点的左儿子就是x
        if (y == y->parent->right)
            y->parent->right = x;
        else
            y->parent->left = x;
    }

    x->right = y;
    y->parent = x;

}

void insert_fixup(Tree* tree, node* now)
{
    node* parent, *gparent;

    //只有被插入节点有父亲节点，并且父亲节点是红色才需要修正
    while ((parent = now->parent) && parent->color == red)
    {
        gparent = parent->parent;

        //判断父亲节点是祖父节点的左儿子还是右儿子
        if (parent == gparent->left)
        {
            node* uncle = gparent->right;
            if (uncle&&uncle->color == red)
            {
                //case 1:当前节点是红色，它的父亲节点是红色，叔叔节点也是红色

                //处理措施：
                //将父亲节点和叔叔节点都变成黑色，祖父节点变成红色
                //并且把祖父节点设为 当前节点
                parent->color = black;
                uncle->color = black;
                gparent->color = red;
                now = gparent;
                continue;
            }

            //case 2:当前节点是父亲节点的右孩子，父亲节点是红色，并且叔叔节点是黑色

            //处理措施：
            //以父亲节点为支点进行左旋
            //把父亲节点作为当前节点，更新父子关系
            if (parent->right == now)
            {
                node* temp;
                LeftRotate(tree, parent);
                /*  左旋前：       gparent            以parent为支点左旋后：  gparent
                *                   /                                         /
                *               parent   uncle                               now   uncle
                *               /                                          /
                *           brothe   now                                parent
                *                                                         /
                *                                                      brothe
                */
                //以父亲节点parent作为当前节点进行左旋之后，parent节点下移成为now的左儿子节点
                //now节点成为parent节点的父亲节点
                //所以这里需要交换，更新谁是父亲节点，谁是当前节点
                temp = parent;
                parent = now;
                now = temp;
            }
            //case 3:当前节点是左儿子，它的父亲节点是红色，叔叔节点是黑色

           //处理措施：
           //将父亲节点设置为黑色
           //祖父节点设置为红色
           //以祖父节点为支点进行右旋
            parent->color = black;
            gparent->color = red;
            RightRotate(tree, gparent);

            //这里父子关系没有变化，所以不用更新

        }
        else//父亲节点是祖父节点的右儿子
        {
            node* uncle = gparent->left;
            if (uncle&&uncle->color == red)
            {
                //case 1:当前节点是红色，它的父亲节点是红色，叔叔节点也是红色

                //处理措施：
                //将父亲节点和叔叔节点都变成黑色，祖父节点变成红色
                //并且把祖父节点设为 当前节点
                parent->color = black;
                uncle->color = black;
                gparent->color = red;
                now = gparent;
                continue;
            }

            //case 2:当前节点是父亲节点的左孩子，父亲节点是红色，并且叔叔节点是黑色

            //处理措施：
            //以父亲节点为支点进行右旋
            //把父亲节点作为当前节点，更新父子关系
            if (parent->left == now)
            {
                /*  右旋前：       gparent            以parent为支点右旋后：  gparent
                *                   /                                         /
                *               parent   uncle                              now   uncle
                *               /
                *           now   brothe                                     parent
                *
                *                                                               brothe
                */
                //以父亲节点parent作为当前节点进右旋之后，parent节点下移成为now的右儿子节点
                //now节点成为parent节点的父亲节点
                //所以这里需要交换，更新谁是父亲节点，谁是当前节点
                node* temp;
                RightRotate(tree, parent);
                temp = parent;
                parent = now;
                now = temp;
            }
            //case 3:当前节点是父亲节点的右儿子，它的父亲节点是红色，叔叔节点是黑色

           //处理措施：
           //将父亲节点设置为黑色
           //祖父节点设置为红色
           //以祖父节点为支点进行左旋
            parent->color = black;
            gparent->color = red;
            LeftRotate(tree, gparent);

            //这里父子关系没有变化，所以不用更新
        }

    }

    //自平衡的核心就是把红色节点上移到根节点，然后把根节点设置为黑色
    tree->root->color = black;
}

void insert(Tree* tree, node* New)
{
    //新建一个节点，暂时保存父节点
    node* temp_parent = NULL;
    //根节点
    node* root = tree->root;

    while (root != NULL)
    {
        temp_parent = root;
        if (New->data < root->data)
            root = root->left;
        else
            root = root->right;
    }

    //找到之后，给新节点new构建关系
    //可以先确定的是，插入新节点new的父节点一定是temp_parent
    New->parent = temp_parent;

    //但是还不确定new是temp_parent的左节点还是右节点
    if (temp_parent != NULL)
    {
        if (New->data < temp_parent->data)
            temp_parent->left = New;
        else
            temp_parent->right = New;
    }
    else
    {
        //父节点为空，说明树为空,则插入的节点就是根节点
        tree->root = New;
    }
    //插入的节点颜色为红
    New->color = red;

    //自平衡修正颜色
    insert_fixup(tree, New);

}

void delect_fixup(Tree* tree, node* now, node* parent)
{
    //now是insert中的替代节点replace
    //now的兄弟节点
    node* brothe;

    //当前节点不是根节点并且为黑色（空节点也认为是黑色）
    while ((now == NULL || now->color == black) && now != tree->root)
    {
        if (parent->left == now)
        {
            brothe = parent->right;
            if (brothe->color == red)
            {
                //Case 1:当前节点是黑+黑，并且兄弟节点是红色
                //策略：
                //1、把兄弟节点变黑，父亲节点变红
                //2、以父亲为支点进行左旋
                //3、左旋后重新设置now的兄弟节点
                brothe->color = black;
                parent->color = red;
                LeftRotate(tree, parent);
                brothe = parent->right;
            }

            if ((brothe->left == NULL || brothe->left->color == black) &&
                (brothe->right == NULL || brothe->right->color == black))
            {
                //Case 2:当前节点是黑+黑，兄弟节点是黑，兄弟节点的左右儿子都是黑（NULL也是黑）
                //策略：
                //1、把兄弟节点变红
                //2、now->parent设置为新的now节点
                brothe->color = red;
                now = now->parent;
                parent = now->parent;
            }
            else
            {
                if (brothe->right == NULL || brothe->right->color == black)
                {
                    //Case 3:当前节点是黑+黑，兄弟节点是黑，兄弟节点的右儿子是黑，左儿子是红
                    //策略：
                    //1、将兄弟节点变红，兄弟节点的左儿子变黑
                    //2、以兄弟节点为支点进行右旋
                    //3、右旋后，重新设置now的兄弟节点
                    brothe->left->color = black;
                    brothe->color = red;
                    RightRotate(tree, brothe);
                    brothe = parent->right;
                }

                //Case 4:当前节点是黑+黑，兄弟节点是黑，兄弟节点的右儿子是红，左儿子是任意颜色
                //策略：（核心是把多余的黑色节点去掉（上升到根节点，然后把根节点设置为黑色））
                //1、将父亲节点的颜色给兄弟节点，将父亲节点变黑，兄弟节点的右儿子节点变黑
                //2、以父亲节点为支点进行左旋
                //3、设置now为根节点
                brothe->color = parent->color;
                parent->color = black;
                brothe->right->color = black;
                LeftRotate(tree, parent);
                now = tree->root;
                break;

            }
        }
        else
        {
            brothe = parent->left;
            if (brothe->color == red)
            {
                //Case 1:当前节点是红+黑，并且兄弟节点是红色
                //策略：
                //1、把兄弟节点变黑，父亲节点变红
                //2、以父亲为支点进行右旋
                //3、右旋后重新设置now的兄弟节点
                brothe->color = black;
                parent->color = red;
                RightRotate(tree, parent);
                brothe = parent->left;
            }

            if ((brothe->left == NULL || brothe->left->color == black) &&
                (brothe->right == NULL || brothe->right->color == black))
            {
                //Case 2:当前节点是红+黑，兄弟节点是黑，兄弟节点的左右儿子都是黑（NULL也是黑）
                //策略：
                //1、把兄弟节点变红
                //2、now->parent设置为新的now节点
                brothe->color = red;
                now = now->parent;
                parent = now->parent;
            }
            else
            {
                if (brothe->left == NULL || brothe->left->color == black)
                {
                    //Case 3:当前节点是红+黑，兄弟节点是黑，兄弟节点的右儿子是黑，左儿子是红
                    //策略：
                    //1、将兄弟节点变红，兄弟节点的右儿子变黑
                    //2、以兄弟节点为支点进行左旋
                    //3、左旋后，重新设置now的兄弟节点
                    brothe->right->color = black;
                    brothe->color = red;
                    LeftRotate(tree, brothe);
                    brothe = parent->left;
                }

                //Case 4:当前节点是红+黑，兄弟节点是黑，兄弟节点的右儿子是红，左儿子是任意颜色
                //策略：（核心是把多余的黑色节点去掉（上升到根节点，然后把根节点设置为黑色））
                //1、将父亲节点的颜色给兄弟节点，将父亲节点变黑，兄弟节点的右儿子节点变黑
                //2、以父亲节点为支点进行右旋
                //3、设置now为根节点
                brothe->color = parent->color;
                parent->color = black;
                brothe->left->color = black;
                RightRotate(tree, parent);
                now = tree->root;
                break;

            }
        }

    }
    if (now != NULL)
        now->color = black;

}
void delect(Tree* tree, node* target)
{
    node* parent, *child;
    int color;

    //既有左子树，又有右子树,在右子树中找后继节点
    if (target->left != NULL && target->right != NULL)
    {
        //找到后继节点（替代节点），用后继节点替换被删除的节点位置
        //然后在删除后继节点的位置
        node* replace = target;
        replace = target->right;
        while (replace->left != NULL)
            replace = replace->left;

        //被删除的节点不是根节点（根节点没有父亲节点）
        if (target->parent != NULL)
        {
            //这里的替换不仅仅是值得替换，还有关系上得替换
            if (target->parent->left == target)
                target->parent->left = replace;
            else
                target->parent->right = replace;
        }
        else
            tree->root = replace;

        //替换完成之后，删除target的问题就转换成删除后继节点的问题
        //现在考虑这个后继节点（replace）：
        //replace节点是target右子树中最小的节点，
        //所以replace要么没有儿子节点，要么只有右儿子节点
        child = replace->right;
        parent = replace->parent;

        //保存后继节点的颜色
        color = replace->color;

        if (target == parent)
        {
            /*           target
            *             /
            *            A  replace
            *
            *///这种情况的话先用replace替换target，然后直接删除replace，
            //只需要更新父亲关系，不用更新replace的儿子的关系（replace没有儿子）
            parent = replace;
        }
        else
        {
            /*情况一：         target          情况二       target
            *                 /                            /
            *                A      B                      A      B
            *                      /                           /
            *                replace   C                   replace  C
            *
            *                    NULL                        child
            *
            */
            if (child != NULL)
            {
                //情况一：直接删除replace,不用调整replace的父子关系
                child->parent = parent;
            }

            //情况二：删除replace,它的后继节点就是child，接下来调整父子关系

            parent->left = child;
            replace->right = target->right;
            target->right->parent = replace;
        }

        //replace替代target之后，调整父子关系
        replace->parent = target->parent;
        replace->left = target->left;
        replace->color = target->color;
        target->left->parent = replace;

        //自平衡：颜色修正
        //如果replace的颜色是红色，把他替换到target位置，replace节点所在支路的黑色节点数量不变
        //如果replace的颜色是黑色，把他替换到target位置，replace节点所在支路的黑色节点数量减一
        //这样违反性质5，又需要继续调整
        if (color == black)
            delect_fixup(tree, child, parent);
        free(target);
        return;
    }
    //只有左子树或右子树，它的左儿子或右儿子就是后继节点
    //child就是replace
    if (target->left != NULL)
        child = target->left;
    else
        child = target->right;

    //确定后继节点之后，开始调整父子关系
    parent = target->parent;
    color = target->color;

    //target为叶子节点
    if (child != NULL)
        child->parent = target;

    //target不为根节点
    if (parent != NULL)
    {
        if (parent->left == target)
            parent->left = child;
        else
            parent->right = child;
    }
    //target为根节点
    else
        tree->root = child;

    //如果target的颜色是黑色的话，破坏性质5
    if (color == black)
        delect_fixup(tree, child, parent);
    free(target);
}
node* search(Tree* tree,int x)
{
    node* root=tree->root;
    while(root!=NULL&&root->data!=x)
    {
        if(x<root->data)
            root=root->left;
        else
            root=root->right;
    }
    return root;
}
void Print(node* root)//前序遍历
{
    if (root == NULL)
        return;
    printf("%d
", root->data);
    Print(root->left);
    Print(root->right);
}
int main()
{
    Tree* tree = new Tree;
    tree->root = NULL;
    int n, x;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> x;
        insert(tree, Creat_Node(x, red, NULL, NULL, NULL));
    }
    Print(tree->root);
    delect(tree,search(tree,4));
    Print(tree->root);
    return 0;
}
