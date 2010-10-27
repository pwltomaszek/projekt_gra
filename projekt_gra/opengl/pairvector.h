#ifndef PAIRVECTOR_H
#define PAIRVECTOR_H

#include <algorithm>
#include <iterator>
#include <vector>

template< typename KeyType, typename ValueType >
class PairVector
{
public:
    ValueType at( const unsigned int &index ) {
        return mValueVector.at( index );
    }

    ValueType at( const KeyType &key ) {
        return find( key );
    }

    KeyType key( const unsigned int &index ) {
        return mKeyVector.at( index );
    }

    KeyType key( const ValueType &value ) {
        typename std::vector< ValueType >::iterator i = std::find( mValueVector.begin(),
                                                                   mValueVector.end(), value );

        if( i == mValueVector.end() )
            return KeyType();

        return mKeyVector.at( distance( mValueVector.begin(), i ) );
    }

    bool contains( const KeyType &key ) {
        typename std::vector< KeyType >::iterator i = std::find( mKeyVector.begin(),
                                                                 mKeyVector.end(), key );

        if( i == mKeyVector.end() )
            return false;

        return true;
    }

    ValueType find( const KeyType &key ) {
        typename std::vector< KeyType >::iterator i = std::find( mKeyVector.begin(),
                                                                 mKeyVector.end(), key );

        if( i == mKeyVector.end() )
            return ValueType();

        return mValueVector.at( distance( mKeyVector.begin(), i ) );
    }

    void push_back( const KeyType &key, const ValueType &value ) {
        mKeyVector.push_back( key );
        mValueVector.push_back( value );
    }

    unsigned int size() const {
        return mKeyVector.size();
    }

    // iterators
    typename std::vector< ValueType >::iterator valuesBegin() {
        return mValueVector.begin();
    }

    typename std::vector< ValueType >::iterator valuesEnd() {
        return mValueVector.end();
    }

    typename std::vector< ValueType >::iterator begin() {
        return mValueVector.begin();
    }

    typename std::vector< ValueType >::iterator end() {
        return mValueVector.end();
    }

    typename std::vector< ValueType >::const_iterator begin() const {
        return mValueVector.begin();
    }

    typename std::vector< ValueType >::const_iterator end() const {
        return mValueVector.end();
    }

private:
    std::vector< KeyType > mKeyVector;
    std::vector< ValueType > mValueVector;
};

#endif // PAIRVECTOR_H
