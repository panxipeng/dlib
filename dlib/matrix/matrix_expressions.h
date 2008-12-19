// Copyright (C) 2006  Davis E. King (davisking@users.sourceforge.net)
// License: Boost Software License   See LICENSE.txt for the full license.
#ifndef DLIB_MATRIx_EXPRESSIONS_H_
#define DLIB_MATRIx_EXPRESSIONS_H_

#include "matrix_fwd.h"

#ifdef _MSC_VER
// This #pragma directive is also located in the algs.h file but for whatever
// reason visual studio 9 just ignores it when it is only there. 

// this is to disable the "'this' : used in base member initializer list"
// warning you get from some of the GUI objects since all the objects
// require that their parent class be passed into their constructor. 
// In this case though it is totally safe so it is ok to disable this warning.
#pragma warning(disable : 4355)
#endif

namespace dlib
{

// ----------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------
//                General matrix expressions that take operator structs
// ----------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------

    template < typename M, typename OP_ >
    class matrix_unary_exp;

    template < typename M, typename OP_ >
    struct matrix_traits<matrix_unary_exp<M,OP_> >
    {
        typedef typename OP_::template op<M> OP;
        typedef typename OP::type type;
        typedef typename OP::mem_manager_type mem_manager_type;
        const static long NR = OP::NR;
        const static long NC = OP::NC;
        const static long cost = OP::cost;
    };

    template <
        typename M,
        typename OP_
        >
    class matrix_unary_exp : public matrix_exp<matrix_unary_exp<M,OP_> >
    {
        /*!
            REQUIREMENTS ON M 
                - must be an object that inherits from matrix_exp
        !*/
        typedef typename OP_::template op<M> OP;

    public:
        typedef typename matrix_traits<matrix_unary_exp>::type type;
        typedef typename matrix_traits<matrix_unary_exp>::mem_manager_type mem_manager_type;
        const static long NR = matrix_traits<matrix_unary_exp>::NR;
        const static long NC = matrix_traits<matrix_unary_exp>::NC;
        const static long cost = matrix_traits<matrix_unary_exp>::cost;

        matrix_unary_exp (
            const M& m_
        ) :
            matrix_exp<matrix_unary_exp>(*this),
            m(m_)
        {}

        const typename OP::type operator() (
            long r, 
            long c
        ) const { return OP::apply(m,r,c); }

        const typename OP::type operator() ( long i ) const 
        { return matrix_exp<matrix_unary_exp>::operator()(i); }

        template <typename U, long iNR, long iNC, typename MM, typename L >
        bool aliases (
            const matrix<U,iNR,iNC,MM,L>& item
        ) const { return m.aliases(item); }

        template <typename U, long iNR, long iNC, typename MM, typename L >
        bool destructively_aliases (
            const matrix<U,iNR,iNC,MM,L>& item
        ) const { return OP::destructively_aliases(m,item); }

        long nr (
        ) const { return OP::nr(m); }

        long nc (
        ) const { return OP::nc(m); }

    private:

        const M& m;
    };

// ----------------------------------------------------------------------------------------

    template < typename M, typename S, typename OP_ >
    class matrix_scalar_binary_exp;

    template < typename M, typename S, typename OP_ >
    struct matrix_traits<matrix_scalar_binary_exp<M,S,OP_> >
    {
        typedef typename OP_::template op<M> OP;
        typedef typename OP::type type;
        typedef typename OP::mem_manager_type mem_manager_type;
        const static long NR = OP::NR;
        const static long NC = OP::NC;
        const static long cost = OP::cost;
    };

    template <
        typename M,
        typename S,
        typename OP_
        >
    class matrix_scalar_binary_exp : public matrix_exp<matrix_scalar_binary_exp<M,S,OP_> > 
    {
        /*!
            REQUIREMENTS ON M 
                - must be an object that inherits from matrix_exp
        !*/
        typedef typename OP_::template op<M> OP;

    public:
        typedef typename matrix_traits<matrix_scalar_binary_exp>::type type;
        typedef typename matrix_traits<matrix_scalar_binary_exp>::mem_manager_type mem_manager_type;
        const static long NR = matrix_traits<matrix_scalar_binary_exp>::NR;
        const static long NC = matrix_traits<matrix_scalar_binary_exp>::NC;
        const static long cost = matrix_traits<matrix_scalar_binary_exp>::cost;

        matrix_scalar_binary_exp (
            const M& m_,
            const S& s_
        ) :
            matrix_exp<matrix_scalar_binary_exp>(*this),
            m(m_),
            s(s_)
        {
            COMPILE_TIME_ASSERT(is_matrix<S>::value == false);
        }

        const typename OP::type operator() (
            long r, 
            long c
        ) const { return OP::apply(m,s,r,c); }

        const typename OP::type operator() ( long i ) const 
        { return matrix_exp<matrix_scalar_binary_exp>::operator()(i); }

        template <typename U, long iNR, long iNC, typename MM, typename L >
        bool aliases (
            const matrix<U,iNR,iNC,MM,L>& item
        ) const { return m.aliases(item); }

        template <typename U, long iNR, long iNC , typename MM, typename L>
        bool destructively_aliases (
            const matrix<U,iNR,iNC,MM,L>& item
        ) const { return OP::destructively_aliases(m,item); }

        long nr (
        ) const { return OP::nr(m); }

        long nc (
        ) const { return OP::nc(m); }

    private:

        const M& m;
        const S s;
    };

// ----------------------------------------------------------------------------------------

    template < typename M, typename S, typename OP_ >
    class matrix_scalar_ternary_exp;

    template < typename M, typename S, typename OP_ >
    struct matrix_traits<matrix_scalar_ternary_exp<M,S,OP_> >
    {
        typedef typename OP_::template op<M> OP;
        typedef typename OP::type type;
        typedef typename OP::mem_manager_type mem_manager_type;
        const static long NR = OP::NR;
        const static long NC = OP::NC;
        const static long cost = OP::cost;
    };

    template <
        typename M,
        typename S,
        typename OP_
        >
    class matrix_scalar_ternary_exp : public matrix_exp<matrix_scalar_ternary_exp<M,S,OP_> > 
    {
        /*!
            REQUIREMENTS ON M 
                - must be an object that inherits from matrix_exp
        !*/
        typedef typename OP_::template op<M> OP;

    public:
        typedef typename matrix_traits<matrix_scalar_ternary_exp>::type type;
        typedef typename matrix_traits<matrix_scalar_ternary_exp>::mem_manager_type mem_manager_type;
        const static long NR = matrix_traits<matrix_scalar_ternary_exp>::NR;
        const static long NC = matrix_traits<matrix_scalar_ternary_exp>::NC;
        const static long cost = matrix_traits<matrix_scalar_ternary_exp>::cost;

        matrix_scalar_ternary_exp (
            const M& m_,
            const S& s1_,
            const S& s2_
        ) :
            matrix_exp<matrix_scalar_ternary_exp>(*this),
            m(m_),
            s1(s1_),
            s2(s2_)
        {
            COMPILE_TIME_ASSERT(is_matrix<S>::value == false);
        }

        const typename OP::type operator() (
            long r, 
            long c
        ) const { return OP::apply(m,s1,s2,r,c); }

        const typename OP::type operator() ( long i ) const 
        { return matrix_exp<matrix_scalar_ternary_exp>::operator()(i); }

        template <typename U, long iNR, long iNC, typename MM, typename L>
        bool aliases (
            const matrix<U,iNR,iNC,MM,L>& item
        ) const { return m.aliases(item); }

        template <typename U, long iNR, long iNC , typename MM, typename L>
        bool destructively_aliases (
            const matrix<U,iNR,iNC,MM,L>& item
        ) const { return OP::destructively_aliases(m,item); }

        long nr (
        ) const { return OP::nr(m); }

        long nc (
        ) const { return OP::nc(m); }

    private:

        const M& m;
        const S s1;
        const S s2;
    };

// ----------------------------------------------------------------------------------------

    template < typename M1, typename M2, typename OP_ >
    class matrix_binary_exp;

    template < typename M1, typename M2, typename OP_ >
    struct matrix_traits<matrix_binary_exp<M1,M2,OP_> >
    {
        typedef typename OP_::template op<M1,M2> OP;
        typedef typename OP::type type;
        typedef typename OP::mem_manager_type mem_manager_type;
        const static long NR = OP::NR;
        const static long NC = OP::NC;
        const static long cost = OP::cost;
    };

    template <
        typename M1,
        typename M2,
        typename OP_
        >
    class matrix_binary_exp : public matrix_exp<matrix_binary_exp<M1,M2,OP_> > 
    {
        /*!
            REQUIREMENTS ON M1 AND M2 
                - must be objects that inherit from matrix_exp
        !*/
        typedef typename OP_::template op<M1,M2> OP;

    public:
        typedef typename matrix_traits<matrix_binary_exp>::type type;
        typedef typename matrix_traits<matrix_binary_exp>::mem_manager_type mem_manager_type;
        const static long NR = matrix_traits<matrix_binary_exp>::NR;
        const static long NC = matrix_traits<matrix_binary_exp>::NC;
        const static long cost = matrix_traits<matrix_binary_exp>::cost;

        matrix_binary_exp (
            const M1& m1_,
            const M2& m2_
        ) :
            matrix_exp<matrix_binary_exp>(*this),
            m1(m1_),
            m2(m2_)
        {}

        const typename OP::type operator() (
            long r, 
            long c
        ) const { return OP::apply(m1,m2,r,c); }

        const typename OP::type operator() ( long i ) const 
        { return matrix_exp<matrix_binary_exp>::operator()(i); }

        template <typename U, long iNR, long iNC, typename MM, typename L >
        bool aliases (
            const matrix<U,iNR,iNC,MM,L>& item
        ) const { return m1.aliases(item) || m2.aliases(item); }

        template <typename U, long iNR, long iNC, typename MM, typename L >
        bool destructively_aliases (
            const matrix<U,iNR,iNC,MM,L>& item
        ) const { return OP::destructively_aliases(m1,m2,item); }

        long nr (
        ) const { return OP::nr(m1,m2); }

        long nc (
        ) const { return OP::nc(m1,m2); }

    private:

        const M1& m1;
        const M2& m2;
    };

// ----------------------------------------------------------------------------------------

    template < typename M1, typename M2, typename M3, typename OP_ >
    class matrix_ternary_exp;

    template < typename M1, typename M2, typename M3, typename OP_ >
    struct matrix_traits<matrix_ternary_exp<M1,M2,M3,OP_> >
    {
        typedef typename OP_::template op<M1,M2,M3> OP;
        typedef typename OP::type type;
        typedef typename OP::mem_manager_type mem_manager_type;
        const static long NR = OP::NR;
        const static long NC = OP::NC;
        const static long cost = OP::cost;
    };

    template <
        typename M1,
        typename M2,
        typename M3,
        typename OP_
        >
    class matrix_ternary_exp : public matrix_exp<matrix_ternary_exp<M1,M2,M3,OP_> > 
    {
        /*!
            REQUIREMENTS ON M1, M2 AND M3
                - must be objects that inherit from matrix_exp
        !*/
        typedef typename OP_::template op<M1,M2,M3> OP;

    public:
        typedef typename matrix_traits<matrix_ternary_exp>::type type;
        typedef typename matrix_traits<matrix_ternary_exp>::mem_manager_type mem_manager_type;
        const static long NR = matrix_traits<matrix_ternary_exp>::NR;
        const static long NC = matrix_traits<matrix_ternary_exp>::NC;
        const static long cost = matrix_traits<matrix_ternary_exp>::cost;

        matrix_ternary_exp (
            const M1& m1_,
            const M2& m2_,
            const M3& m3_
        ) :
            matrix_exp<matrix_ternary_exp>(*this),
            m1(m1_),
            m2(m2_),
            m3(m3_)
        {}

        const typename OP::type operator() (
            long r, 
            long c
        ) const { return OP::apply(m1,m2,m3,r,c); }

        const typename OP::type operator() ( long i ) const 
        { return matrix_exp<matrix_ternary_exp>::operator()(i); }

        template <typename U, long iNR, long iNC, typename MM, typename L >
        bool aliases (
            const matrix<U,iNR,iNC,MM,L>& item
        ) const { return m1.aliases(item) || m2.aliases(item) || m3.aliases(item); }

        template <typename U, long iNR, long iNC, typename MM, typename L >
        bool destructively_aliases (
            const matrix<U,iNR,iNC,MM,L>& item
        ) const { return OP::destructively_aliases(m1,m2,m3,item); }

        long nr (
        ) const { return OP::nr(m1,m2,m3); }

        long nc (
        ) const { return OP::nc(m1,m2,m3); }

    private:

        const M1& m1;
        const M2& m2;
        const M3& m3;
    };

// ----------------------------------------------------------------------------------------

    template < typename M1, typename M2, typename M3, typename M4, typename OP_ >
    class matrix_fourary_exp;

    template < typename M1, typename M2, typename M3, typename M4, typename OP_ >
    struct matrix_traits<matrix_fourary_exp<M1,M2,M3,M4,OP_> >
    {
        typedef typename OP_::template op<M1,M2,M3,M4> OP;
        typedef typename OP::type type;
        typedef typename OP::mem_manager_type mem_manager_type;
        const static long NR = OP::NR;
        const static long NC = OP::NC;
        const static long cost = OP::cost;
    };

    template <
        typename M1,
        typename M2,
        typename M3,
        typename M4,
        typename OP_
        >
    class matrix_fourary_exp : public matrix_exp<matrix_fourary_exp<M1,M2,M3,M4,OP_> > 
    {
        /*!
            REQUIREMENTS ON M1, M2, M3 AND M4
                - must be objects that inherit from matrix_exp
        !*/
        typedef typename OP_::template op<M1,M2,M3,M4> OP;

    public:
        typedef typename matrix_traits<matrix_fourary_exp>::type type;
        typedef typename matrix_traits<matrix_fourary_exp>::mem_manager_type mem_manager_type;
        const static long NR = matrix_traits<matrix_fourary_exp>::NR;
        const static long NC = matrix_traits<matrix_fourary_exp>::NC;
        const static long cost = matrix_traits<matrix_fourary_exp>::cost;

        matrix_fourary_exp (
            const M1& m1_,
            const M2& m2_,
            const M3& m3_,
            const M4& m4_
        ) :
            matrix_exp<matrix_fourary_exp>(*this),
            m1(m1_),
            m2(m2_),
            m3(m3_),
            m4(m4_)
        {}

        const typename OP::type operator() (
            long r, 
            long c
        ) const { return OP::apply(m1,m2,m3,m4,r,c); }

        const typename OP::type operator() ( long i ) const 
        { return matrix_exp<matrix_fourary_exp>::operator()(i); }

        template <typename U, long iNR, long iNC, typename MM, typename L >
        bool aliases (
            const matrix<U,iNR,iNC,MM,L>& item
        ) const { return m1.aliases(item) || m2.aliases(item) || m3.aliases(item) || m4.aliases(item); }

        template <typename U, long iNR, long iNC, typename MM, typename L >
        bool destructively_aliases (
            const matrix<U,iNR,iNC,MM,L>& item
        ) const { return OP::destructively_aliases(m1,m2,m3,m4,item); }

        long nr (
        ) const { return OP::nr(m1,m2,m3,m4); }

        long nc (
        ) const { return OP::nc(m1,m2,m3,m4); }

    private:

        const M1& m1;
        const M2& m2;
        const M3& m3;
        const M4& m4;
    };

// ----------------------------------------------------------------------------------------

    template < typename S, typename OP >
    class dynamic_matrix_scalar_unary_exp;

    template < typename S, typename OP >
    struct matrix_traits<dynamic_matrix_scalar_unary_exp<S,OP> >
    {
        typedef typename OP::type type;
        typedef typename OP::mem_manager_type mem_manager_type;
        const static long NR = OP::NR;
        const static long NC = OP::NC;
        const static long cost = OP::cost;
    };

    template <
        typename S,
        typename OP
        >
    class dynamic_matrix_scalar_unary_exp : public matrix_exp<dynamic_matrix_scalar_unary_exp<S,OP> >
    {
        /*!
            REQUIREMENTS ON S 
                should be some scalar type
        !*/
    public:
        typedef typename matrix_traits<dynamic_matrix_scalar_unary_exp>::type type;
        typedef typename matrix_traits<dynamic_matrix_scalar_unary_exp>::mem_manager_type mem_manager_type;
        const static long NR = matrix_traits<dynamic_matrix_scalar_unary_exp>::NR;
        const static long NC = matrix_traits<dynamic_matrix_scalar_unary_exp>::NC;
        const static long cost = matrix_traits<dynamic_matrix_scalar_unary_exp>::cost;


        dynamic_matrix_scalar_unary_exp (
            long nr__,
            long nc__,
            const S& s_
        ) :
            matrix_exp<dynamic_matrix_scalar_unary_exp>(*this),
            nr_(nr__),
            nc_(nc__),
            s(s_)
        {
            COMPILE_TIME_ASSERT(is_matrix<S>::value == false);
        }

        const typename OP::type operator() (
            long r, 
            long c
        ) const { return OP::apply(s,r,c); }

        const typename OP::type operator() ( long i ) const 
        { return matrix_exp<dynamic_matrix_scalar_unary_exp>::operator()(i); }

        template <typename U, long iNR, long iNC, typename MM, typename L >
        bool aliases (
            const matrix<U,iNR,iNC,MM,L>& item
        ) const { return false; }

        template <typename U, long iNR, long iNC , typename MM, typename L>
        bool destructively_aliases (
            const matrix<U,iNR,iNC,MM,L>& item
        ) const { return false; }

        long nr (
        ) const { return nr_; }

        long nc (
        ) const { return nc_; }

    private:

        const long nr_;
        const long nc_;
        const S s;
    };

// ----------------------------------------------------------------------------------------

    template <typename S, typename OP>
    class matrix_scalar_unary_exp;

    template <typename S, typename OP>
    struct matrix_traits<matrix_scalar_unary_exp<S,OP> >
    {
        typedef typename OP::type type;
        typedef typename OP::mem_manager_type mem_manager_type;
        const static long NR = OP::NR;
        const static long NC = OP::NC;
        const static long cost = OP::cost;
    };

    template <
        typename S,
        typename OP
        >
    class matrix_scalar_unary_exp : public matrix_exp<matrix_scalar_unary_exp<S,OP> >
    {
        /*!
            REQUIREMENTS ON S 
                should be some scalar type
        !*/
    public:
        typedef typename matrix_traits<matrix_scalar_unary_exp>::type type;
        typedef typename matrix_traits<matrix_scalar_unary_exp>::mem_manager_type mem_manager_type;
        const static long NR = matrix_traits<matrix_scalar_unary_exp>::NR;
        const static long NC = matrix_traits<matrix_scalar_unary_exp>::NC;
        const static long cost = matrix_traits<matrix_scalar_unary_exp>::cost;

        matrix_scalar_unary_exp (
            const S& s_
        ) :
            matrix_exp<matrix_scalar_unary_exp>(*this),
            s(s_)
        {
            COMPILE_TIME_ASSERT(is_matrix<S>::value == false);
        }

        const typename OP::type operator() (
            long r, 
            long c
        ) const { return OP::apply(s,r,c); }

        const typename OP::type operator() ( long i ) const 
        { return matrix_exp<matrix_scalar_unary_exp>::operator()(i); }

        template <typename U, long iNR, long iNC, typename MM, typename L >
        bool aliases (
            const matrix<U,iNR,iNC,MM,L>& item
        ) const { return false; }

        template <typename U, long iNR, long iNC, typename MM, typename L >
        bool destructively_aliases (
            const matrix<U,iNR,iNC,MM,L>& item
        ) const { return false; }

        long nr (
        ) const { return NR; }

        long nc (
        ) const { return NC; }

    private:

        const S s;
    };

// ----------------------------------------------------------------------------------------

    template <typename OP>
    class matrix_zeroary_exp;

    template <typename OP>
    struct matrix_traits<matrix_zeroary_exp<OP> >
    {
        typedef typename OP::type type;
        typedef typename OP::mem_manager_type mem_manager_type;
        const static long NR = OP::NR;
        const static long NC = OP::NC;
        const static long cost = OP::cost;
    };

    template <
        typename OP
        >
    class matrix_zeroary_exp : public matrix_exp<matrix_zeroary_exp<OP> >
    {
    public:
        typedef typename matrix_traits<matrix_zeroary_exp>::type type;
        typedef typename matrix_traits<matrix_zeroary_exp>::mem_manager_type mem_manager_type;
        const static long NR = matrix_traits<matrix_zeroary_exp>::NR;
        const static long NC = matrix_traits<matrix_zeroary_exp>::NC;
        const static long cost = matrix_traits<matrix_zeroary_exp>::cost;

        matrix_zeroary_exp (
        ) :
            matrix_exp<matrix_zeroary_exp>(*this)
        {}

        const typename OP::type operator() (
            long r, 
            long c
        ) const { return OP::apply(r,c); }

        const typename OP::type operator() ( long i ) const 
        { return matrix_exp<matrix_zeroary_exp>::operator()(i); }

        template <typename U, long iNR, long iNC , typename MM, typename L>
        bool aliases (
            const matrix<U,iNR,iNC,MM,L>& item
        ) const { return false; }

        template <typename U, long iNR, long iNC, typename MM, typename L >
        bool destructively_aliases (
            const matrix<U,iNR,iNC,MM,L>& item
        ) const { return false; }

        long nr (
        ) const { return NR; }

        long nc (
        ) const { return NC; }

    };

// ----------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------
//                           Specialized matrix expressions 
// ----------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------

    template < typename M, typename EXPr, typename EXPc >
    class matrix_sub_range_exp;

    template < typename M, typename EXPr, typename EXPc >
    struct matrix_traits<matrix_sub_range_exp<M,EXPr,EXPc> >
    {
        typedef typename M::type type;
        typedef typename M::mem_manager_type mem_manager_type;
        const static long NR = EXPr::NR*EXPr::NC;
        const static long NC = EXPc::NR*EXPr::NC;
        const static long cost = EXPr::cost+EXPc::cost+M::cost;
    };

    template <
        typename M,
        typename EXPr,
        typename EXPc
        >
    class matrix_sub_range_exp : public matrix_exp<matrix_sub_range_exp<M,EXPr,EXPc> > 
    {
        /*!
            REQUIREMENTS ON M, EXPr and EXPc
                - must be objects that inherit from matrix_exp
        !*/
    public:
        typedef typename matrix_traits<matrix_sub_range_exp>::type type;
        typedef typename matrix_traits<matrix_sub_range_exp>::mem_manager_type mem_manager_type;
        const static long NR = matrix_traits<matrix_sub_range_exp>::NR;
        const static long NC = matrix_traits<matrix_sub_range_exp>::NC;
        const static long cost = matrix_traits<matrix_sub_range_exp>::cost;

        matrix_sub_range_exp (
            const M& m_,
            const EXPr& rows_,
            const EXPc& cols_
        ) :
            matrix_exp<matrix_sub_range_exp>(*this),
            m(m_),
            rows(rows_),
            cols(cols_)
        {
        }

        const typename M::type operator() (
            long r, 
            long c
        ) const { return m(rows(r),cols(c)); }

        const typename M::type operator() ( long i ) const 
        { return matrix_exp<matrix_sub_range_exp>::operator()(i); }

        template <typename U, long iNR, long iNC, typename MM, typename L >
        bool aliases (
            const matrix<U,iNR,iNC,MM,L>& item
        ) const { return m.aliases(item) || rows.aliases(item) || cols.aliases(item); }

        template <typename U, long iNR, long iNC , typename MM, typename L>
        bool destructively_aliases (
            const matrix<U,iNR,iNC,MM,L>& item
        ) const { return m.aliases(item) || rows.aliases(item) || cols.aliases(item); }

        long nr (
        ) const { return rows.size(); }

        long nc (
        ) const { return cols.size(); }

    private:

        const M& m;
        const EXPr& rows;
        const EXPc& cols;
    };

// ----------------------------------------------------------------------------------------

    template <typename M>
    class matrix_std_vector_exp;

    template <typename M>
    struct matrix_traits<matrix_std_vector_exp<M> >
    {
        typedef typename M::value_type type;
        typedef typename memory_manager<char>::kernel_1a mem_manager_type;
        const static long NR = 0;
        const static long NC = 1;
        const static long cost = 1;
    };

    template <
        typename M
        >
    class matrix_std_vector_exp : public matrix_exp<matrix_std_vector_exp<M> > 
    {
        /*!
            REQUIREMENTS ON M 
                - must be a std::vector object (or
                  an object with a compatible interface).
        !*/
    public:
        typedef typename matrix_traits<matrix_std_vector_exp>::type type;
        typedef typename matrix_traits<matrix_std_vector_exp>::mem_manager_type mem_manager_type;
        const static long NR = matrix_traits<matrix_std_vector_exp>::NR;
        const static long NC = matrix_traits<matrix_std_vector_exp>::NC;
        const static long cost = matrix_traits<matrix_std_vector_exp>::cost;

        matrix_std_vector_exp (
            const M& m_
        ) :
            matrix_exp<matrix_std_vector_exp>(*this),
            m(m_)
        {
        }

        const typename M::value_type operator() (
            long r, 
            long 
        ) const { return m[r]; }

        const typename M::value_type operator() ( long i ) const 
        { return m[i]; }

        template <typename U, long iNR, long iNC, typename MM, typename L>
        bool aliases (
            const matrix<U,iNR,iNC,MM,L>& item
        ) const { return false; }

        template <typename U, long iNR, long iNC , typename MM, typename L>
        bool destructively_aliases (
            const matrix<U,iNR,iNC,MM,L>& item
        ) const { return false; }

        long nr (
        ) const { return m.size(); }

        long nc (
        ) const { return 1; }

    private:
        const M& m;
    };

// ----------------------------------------------------------------------------------------

    template <typename M>
    class matrix_array_exp;

    template <typename M>
    struct matrix_traits<matrix_array_exp<M> >
    {
        typedef typename M::type type;
        typedef typename M::mem_manager_type mem_manager_type;
        const static long NR = 0;
        const static long NC = 1;
        const static long cost = 1;
    };

    template <
        typename M
        >
    class matrix_array_exp : public matrix_exp<matrix_array_exp<M> >
    {
        /*!
            REQUIREMENTS ON M 
                - must be a dlib::array object (or
                  an object with a compatible interface).
        !*/
    public:
        typedef typename matrix_traits<matrix_array_exp>::type type;
        typedef typename matrix_traits<matrix_array_exp>::mem_manager_type mem_manager_type;
        const static long NR = matrix_traits<matrix_array_exp>::NR;
        const static long NC = matrix_traits<matrix_array_exp>::NC;
        const static long cost = matrix_traits<matrix_array_exp>::cost;

        matrix_array_exp (
            const M& m_
        ) :
            matrix_exp<matrix_array_exp>(*this),
            m(m_)
        {
        }

        const typename M::type operator() (
            long r, 
            long 
        ) const { return m[r]; }

        const typename M::type operator() ( long i ) const 
        { return m[i]; }

        template <typename U, long iNR, long iNC, typename MM, typename L>
        bool aliases (
            const matrix<U,iNR,iNC,MM,L>& item
        ) const { return false; }

        template <typename U, long iNR, long iNC , typename MM, typename L>
        bool destructively_aliases (
            const matrix<U,iNR,iNC,MM,L>& item
        ) const { return false; }

        long nr (
        ) const { return m.size(); }

        long nc (
        ) const { return 1; }

    private:
        const M& m;
    };

// ----------------------------------------------------------------------------------------

    template <typename M>
    class matrix_array2d_exp;

    template <typename M>
    struct matrix_traits<matrix_array2d_exp<M> >
    {
        typedef typename M::type type;
        typedef typename M::mem_manager_type mem_manager_type;
        const static long NR = 0;
        const static long NC = 0;
        const static long cost = 1;
    };

    template <
        typename M
        >
    class matrix_array2d_exp : public matrix_exp<matrix_array2d_exp<M> > 
    {
        /*!
            REQUIREMENTS ON M 
                - must be a dlib::array2d object (or
                  an object with a compatible interface).
        !*/
    public:
        typedef typename matrix_traits<matrix_array2d_exp>::type type;
        typedef typename matrix_traits<matrix_array2d_exp>::mem_manager_type mem_manager_type;
        const static long NR = matrix_traits<matrix_array2d_exp>::NR;
        const static long NC = matrix_traits<matrix_array2d_exp>::NC;
        const static long cost = matrix_traits<matrix_array2d_exp>::cost;

        matrix_array2d_exp (
            const M& m_
        ) :
            matrix_exp<matrix_array2d_exp>(*this),
            m(m_)
        {
        }

        const typename M::type operator() (
            long r, 
            long c
        ) const { return m[r][c]; }

        const typename M::type operator() ( long i ) const 
        { return matrix_exp<matrix_array2d_exp>::operator()(i); }

        template <typename U, long iNR, long iNC, typename MM, typename L>
        bool aliases (
            const matrix<U,iNR,iNC,MM,L>& item
        ) const { return false; }

        template <typename U, long iNR, long iNC , typename MM, typename L>
        bool destructively_aliases (
            const matrix<U,iNR,iNC,MM,L>& item
        ) const { return false; }

        long nr (
        ) const { return m.nr(); }

        long nc (
        ) const { return m.nc(); }

    private:
        const M& m;
    };

// ----------------------------------------------------------------------------------------

    template <typename M>
    class matrix_sub_exp;

    template <typename M>
    struct matrix_traits<matrix_sub_exp<M> >
    {
        typedef typename M::type type;
        typedef typename M::mem_manager_type mem_manager_type;
        const static long NR = 0;
        const static long NC = 0;
        const static long cost = M::cost+1;
    };

    template <
        typename M
        >
    class matrix_sub_exp : public matrix_exp<matrix_sub_exp<M> >
    {
        /*!
            REQUIREMENTS ON M 
                - must be an object that inherits from matrix_exp
        !*/
    public:
        typedef typename matrix_traits<matrix_sub_exp>::type type;
        typedef typename matrix_traits<matrix_sub_exp>::mem_manager_type mem_manager_type;
        const static long NR = matrix_traits<matrix_sub_exp>::NR;
        const static long NC = matrix_traits<matrix_sub_exp>::NC;
        const static long cost = matrix_traits<matrix_sub_exp>::cost;

        matrix_sub_exp (
            const M& m_,
            const long& r__,
            const long& c__,
            const long& nr__,
            const long& nc__
        ) :
            matrix_exp<matrix_sub_exp>(*this),
            m(m_),
            r_(r__),
            c_(c__),
            nr_(nr__),
            nc_(nc__)
        {
        }

        const typename M::type operator() (
            long r, 
            long c
        ) const { return m(r+r_,c+c_); }

        const typename M::type operator() ( long i ) const 
        { return matrix_exp<matrix_sub_exp>::operator()(i); }

        template <typename U, long iNR, long iNC, typename MM, typename L >
        bool aliases (
            const matrix<U,iNR,iNC,MM,L>& item
        ) const { return m.aliases(item); }

        template <typename U, long iNR, long iNC , typename MM, typename L>
        bool destructively_aliases (
            const matrix<U,iNR,iNC,MM,L>& item
        ) const { return m.aliases(item); }

        long nr (
        ) const { return nr_; }

        long nc (
        ) const { return nc_; }

    private:

        const M& m;
        const long r_, c_, nr_, nc_;
    };

// ----------------------------------------------------------------------------------------

    class matrix_range_exp;

    template <>
    struct matrix_traits<matrix_range_exp>
    {
        typedef long type;
        typedef memory_manager<char>::kernel_1a mem_manager_type;
        const static long NR = 0;
        const static long NC = 1;
        const static long cost = 1;
    };

    class matrix_range_exp : public matrix_exp<matrix_range_exp>
    {
    public:
        typedef matrix_traits<matrix_range_exp>::type type;
        typedef matrix_traits<matrix_range_exp>::mem_manager_type mem_manager_type;
        const static long NR = matrix_traits<matrix_range_exp>::NR;
        const static long NC = matrix_traits<matrix_range_exp>::NC;
        const static long cost = matrix_traits<matrix_range_exp>::cost;

        matrix_range_exp (
            long start_,
            long end_
        ) :
            matrix_exp<matrix_range_exp>(*this)
        {
            start = start_;
            if (start_ <= end_)
                inc = 1;
            else 
                inc = -1;
            nr_ = std::abs(end_ - start_) + 1;
        }
        matrix_range_exp (
            long start_,
            long inc_,
            long end_
        ) :
            matrix_exp<matrix_range_exp>(*this)
        {
            start = start_;
            nr_ = std::abs(end_ - start_)/inc_ + 1;
            if (start_ <= end_)
                inc = inc_;
            else
                inc = -inc_;
        }

        long operator() (
            long r, 
            long c
        ) const { return start + r*inc;  }

        long operator() (
            long r
        ) const { return start + r*inc;  }

        template <typename U, long iNR, long iNC , typename MM, typename L>
        bool aliases (
            const matrix<U,iNR,iNC,MM,L>& item
        ) const { return false; }

        template <typename U, long iNR, long iNC, typename MM, typename L >
        bool destructively_aliases (
            const matrix<U,iNR,iNC,MM,L>& item
        ) const { return false; }

        long nr (
        ) const { return nr_; }

        long nc (
        ) const { return NC; }

        long nr_;
        long start;
        long inc;
    };

// ----------------------------------------------------------------------------------------

    template <long start, long inc_, long end>
    class matrix_range_static_exp;

    template <long start, long inc_, long end>
    struct matrix_traits<matrix_range_static_exp<start,inc_,end> >
    {
        typedef long type;
        typedef memory_manager<char>::kernel_1a mem_manager_type;
        const static long NR = tabs<(end - start)>::value/inc_ + 1;
        const static long NC = 1;
        const static long cost = 1;
    };

    template <long start, long inc_, long end>
    class matrix_range_static_exp : public matrix_exp<matrix_range_static_exp<start,inc_,end> > 
    {
    public:
        typedef typename matrix_traits<matrix_range_static_exp>::type type;
        typedef typename matrix_traits<matrix_range_static_exp>::mem_manager_type mem_manager_type;
        const static long NR = matrix_traits<matrix_range_static_exp>::NR;
        const static long NC = matrix_traits<matrix_range_static_exp>::NC;
        const static long cost = matrix_traits<matrix_range_static_exp>::cost;

        const static long inc = (start <= end)?inc_:-inc_;

        matrix_range_static_exp (
        ) :
            matrix_exp<matrix_range_static_exp>(*this)
        {}

        long operator() (
            long r, 
            long c
        ) const { return start + r*inc;  }

        long operator() (
            long r
        ) const { return start + r*inc;  }

        template <typename U, long iNR, long iNC , typename MM, typename L>
        bool aliases (
            const matrix<U,iNR,iNC,MM,L>& item
        ) const { return false; }

        template <typename U, long iNR, long iNC, typename MM, typename L >
        bool destructively_aliases (
            const matrix<U,iNR,iNC,MM,L>& item
        ) const { return false; }

        long nr (
        ) const { return NR; }

        long nc (
        ) const { return NC; }

    };

// ----------------------------------------------------------------------------------------

}

#endif // DLIB_MATRIx_UTILITIES_

