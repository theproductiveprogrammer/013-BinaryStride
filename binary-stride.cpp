/**
 * Binary Stride v/s Binary Search
 */
/**
 * In this blog, we take a look
 * at an iconic staple of
 * computer science algorithms –
 * the trusty binary search and
 * find that it still holds some
 * surprises.
 *
 * By now you should know that
 * binary search is one of the
 * most effective ways to search
 * a sorted array – splitting it
 * in half at every iteration to
 * give us an O(logn) solution.
 *
 * The way it works is also
 * simple and elegant:
 *
 *  _*Find the midpoint
 *  then go left or right*_
 *
 * Think about how you
 * naturally look for words in a
 * dictionary or numbers in a
 * phone book and you’ve got the
 * idea.
 *
 * This is such a simple idea
 * that I assumed it was a
 * trivial algorithm to
 * implement. My curiosity about
 * binary search was first
 * aroused when I read about it
 * in the excellent book
 * "Beautiful Code".
 */
/**
 * beautiful-code.gif [href=https://www.amazon.com/Beautiful-Code-Leading-Programmers-Practice/dp/0596510047]
 */
/**
 * Here I learned that although
 * the basic idea of binary
 * search is simple, its
 * implementation can be
 * surprisingly tricky!
 */
/**
 * *_When Jon Bentley assigned
 * binary search as a problem in
 * a course for professional
 * programmers, he found that
 * ninety percent failed to
 * provide a correct solution
 * after several hours of
 * working on it! Another study
 * published in 1988 shows that
 * accurate code for it is was
 * only found in five out of
 * twenty textbooks.
 *
 * Fascinatingly, Bentley’s own
 * implementation of binary
 * search, published in his 1986
 * book Programming Pearls,
 * contained an overflow error
 * that remained undetected for
 * over twenty years. The Java
 * programming language library
 * implementation of binary
 * search had the same overflow
 * bug for more than nine years._*
 */
/**
 * If you'd like to see why it
 * is so tricky I highly
 * recommend the excellent
 * article on [href=https://www.topcoder.com/community/data-science/data-science-tutorials/binary-search/](TopCoder)
 */
/**
 * What prompted me to write
 * this blog, though, was I
 * found another variant of
 * the binary search algorithm
 * that is _much easier to
 * implement_ and helps us look
 * at this old problem in a
 * different and interesting
 * way.
 *
 * I call this method the
 * "binary stride" version and I
 * will describe it below.
 */
/**
 * *__Standard Binary Search__*
 *
 * Let's refresh our
 * understanding of the binary
 * search by looking at a
 * visualization (click-to-expand)
 * and a correct implementation:
 */
/**
 * binary-search.gif [href=/013/binary-search.png]
 */
#include <iostream>

int binary_search(int a[], int sz, int needle) {
    int l = 0, r = sz - 1;
    while(l <= r) {
        int mid = (l + r) >> 1;
        if(a[mid] == needle) return mid;
        if(a[mid] < needle) l = mid+1;
        else r = mid-1;
    }
    return -1;
}

/**
 * *__Binary Stride__*
 *
 * Now let's understand the
 * _stride_ version. Here the
 * idea is slightly different
 * and very interesting.
 *
 * First let’s be clear that
 * binary search is only
 * efficient when we have random
 * access. If we have to walk
 * step by step (like a linked
 * list) then a linear search
 * would make more sense.
 *
 * So at the beginning, we know
 * we can make jumps to
 * random points in our search
 * space efficiently.
 *
 * The stride version uses this
 * in it’s idea – let’s make
 * large jumps and only slow the
 * speed as we get closer to our
 * target.
 */
/**
 * binary-stride.gif [href=/013/binary-stride.png]
 */
/**
 * Our search goes through the
 * array from left to right.
 *
 * The initial jump length is
 * n/2. At each step, the jump
 * length will be halved: first
 * n/4, then n/8, n/16, etc.,
 * until finally the length is
 * 1.
 *
 * After the jumps, either
 * the target element has been
 * found or we know that it does
 * not appear in the array.
 */
/**
 * The following code implements
 * the binary stride version:
 */
int binary_stride(int a[], int sz, int needle) {
    int pos = 0;
    for(int stride = sz/2;stride >= 1;stride /= 2) {
        while(pos+stride < sz && a[pos+stride] <= needle) pos += stride;
    }
    if(a[pos] == needle) return pos;
    return -1;
}

/**
 * *__Why Stride?__*
 *
 * The stride formulation is
 * interesting and intuitive but
 * there is a better reason you
 * should know about it. If you
 * have [href=https://www.topcoder.com/community/data-science/data-science-tutorials/binary-search/](read the article on
 * topcoder), you
 * will see the complications in
 * binary search start mounting
 * when we use in in a
 * generalized search rather
 * than a fixed array.
 *
 * Binary search can be used in
 * a generalized way to answer
 * questions about a function
 * and this turns out to be
 * pretty useful.
 *
 * For example, let us assume we
 * need to find the point in an
 * array where the graph becomes
 * positive.
 */
/**
 * graph.png
 */
/**
 * This is where the binary
 * search becomes tricky while the
 * stride version remains a very
 * natural fit:
 */
int find_crossover_point(int a[], int sz) {
    int pos = 0;
    for(int stride = sz/2;stride >= 1;stride /= 2) {
        while(fn(a[pos+stride]) <= 0) pos += stride;
    }
    return pos;
}

/**
 * I hope you found the binary
 * stride as interesting as I
 * did and have a new tool for
 * your thinking toolbox!
 */

/* tests */
int main() {
    int a1[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    int a2[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    int a3[] = { 4 };
    int a4[] = { 1, 4, 9 };
    int a5[] = { 1, 4 };
    int a6[] = { 4, 9 };
    int a7[] = { };

    std::cout << binary_stride(a1, sizeof(a1)/sizeof(a1[0]), 4) << '\n';
    std::cout << binary_stride(a2, sizeof(a2)/sizeof(a2[0]), 4) << '\n';
    std::cout << binary_stride(a3, sizeof(a3)/sizeof(a3[0]), 4) << '\n';
    std::cout << binary_stride(a4, sizeof(a4)/sizeof(a4[0]), 4) << '\n';
    std::cout << binary_stride(a5, sizeof(a5)/sizeof(a5[0]), 4) << '\n';
    std::cout << binary_stride(a6, sizeof(a6)/sizeof(a6[0]), 4) << '\n';
    std::cout << binary_stride(a7, sizeof(a7)/sizeof(a7[0]), 4) << '\n';

    std::cout << a1[binary_stride(a1, sizeof(a1)/sizeof(a1[0]), 4)] << '\n';
    std::cout << a2[binary_stride(a2, sizeof(a2)/sizeof(a2[0]), 4)] << '\n';
    std::cout << a3[binary_stride(a3, sizeof(a3)/sizeof(a3[0]), 4)] << '\n';
    std::cout << a4[binary_stride(a4, sizeof(a4)/sizeof(a4[0]), 4)] << '\n';
    std::cout << a5[binary_stride(a5, sizeof(a5)/sizeof(a5[0]), 4)] << '\n';
    std::cout << a6[binary_stride(a6, sizeof(a6)/sizeof(a6[0]), 4)] << '\n';

    std::cout << binary_stride(a1, sizeof(a1)/sizeof(a1[0]), 14) << '\n';
    std::cout << binary_stride(a2, sizeof(a2)/sizeof(a2[0]), 14) << '\n';
    std::cout << binary_stride(a3, sizeof(a3)/sizeof(a3[0]), 14) << '\n';
    std::cout << binary_stride(a4, sizeof(a4)/sizeof(a4[0]), 14) << '\n';
    std::cout << binary_stride(a5, sizeof(a5)/sizeof(a5[0]), 14) << '\n';
    std::cout << binary_stride(a6, sizeof(a6)/sizeof(a6[0]), 14) << '\n';

    std::cout << binary_stride(a1, sizeof(a1)/sizeof(a1[0]), 0) << '\n';
    std::cout << binary_stride(a2, sizeof(a2)/sizeof(a2[0]), 0) << '\n';
    std::cout << binary_stride(a3, sizeof(a3)/sizeof(a3[0]), 0) << '\n';
    std::cout << binary_stride(a4, sizeof(a4)/sizeof(a4[0]), 0) << '\n';
    std::cout << binary_stride(a5, sizeof(a5)/sizeof(a5[0]), 0) << '\n';
    std::cout << binary_stride(a6, sizeof(a6)/sizeof(a6[0]), 0) << '\n';
}

