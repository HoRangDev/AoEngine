#pragma once

template <typename Ty>
class AoPtrWrapper
{
public:
	AoPtrWrapper( Ty* Value );
	~AoPtrWrapper( );

	Ty& operator*( );

	bool IsNullptr( ) const;

private:
	Ty* Ptr;

};

template <typename Ty>
AoPtrWrapper<Ty>::AoPtrWrapper( Ty* Value )
	: Ptr( Value )
{

}

template <typename Ty>
AoPtrWrapper<Ty>::~AoPtrWrapper( )
{

}

template <typename Ty>
Ty& AoPtrWrapper<Ty>::operator*( )
{
	return ( *Ptr );
}

template <typename Ty>
bool AoPtrWrapper<Ty>::IsNullptr( ) const
{
	return ( Ptr == nullptr );
}