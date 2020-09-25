#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <sstream>
#include <string>
#include "doctest.h"
#include "avl.h"

TEST_CASE("Right rotation")
{
    Avl::Node<int> root(15);
    Avl::Node<int> l1(12);
    Avl::Node<int> r1(17);
    Avl::Node<int> r2(20);
    Avl::Node<int> l3(18);
    Avl::Node<int> r3(30);

    r2.height = 1;
    r2.left = &l3;
    r2.right = &r3;

    r1.height = 2;
    r1.right = &r2;

    root.height = 3;
    root.left = &l1;
    root.right = &r1;

    Avl::Node<int> *rp = &root;
    Avl::rotateRight(rp);

    REQUIRE(rp != nullptr);
    CHECK(rp->height == 2);
    CHECK(rp->key == 17);

    Avl::Node<int> *nl = rp->left;
    Avl::Node<int> *nr = rp->right;

    REQUIRE(nl != nullptr);
    CHECK(nl->height == 1);
    CHECK(nl->key == 15);

    REQUIRE(nr != nullptr);
    CHECK(nr->height == 1);
    CHECK(nr->key == 20);
}

TEST_CASE("Left rotation")
{
    Avl::Node<int> root(25);
    Avl::Node<int> l1(18);
    Avl::Node<int> r1(30);
    Avl::Node<int> l2(17);
    Avl::Node<int> r2(23);
    Avl::Node<int> l3(12);

    l2.height = 1;
    l2.left = &l3;

    l1.height = 2;
    l1.left  = &l2;
    l1.right = &r2;

    root.height = 3;
    root.left = &l1;
    root.right = &r1;

    Avl::Node<int> *rp = &root;
    Avl::rotateLeft(rp);

    REQUIRE(rp != nullptr);
    CHECK(rp->height == 2);
    CHECK(rp->key == 18);

    Avl::Node<int> *nl = rp->left;
    Avl::Node<int> *nr = rp->right;

    REQUIRE(nl != nullptr);
    CHECK(nl->height == 1);
    CHECK(nl->key == 17);

    REQUIRE(nr != nullptr);
    CHECK(nr->height == 1);
    CHECK(nr->key == 25);

    rp = nr;
    nl = rp->left;
    nr = rp->right;

    REQUIRE(nl != nullptr);
    CHECK(nl->height == 0);
    CHECK(nl->key == 23);

    REQUIRE(nr != nullptr);
    CHECK(nr->height == 0);
    CHECK(nr->key == 30);
}