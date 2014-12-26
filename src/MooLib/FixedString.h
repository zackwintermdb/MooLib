#pragma once

namespace ml {

template <class _CharT, class _Traits, size_t _Size>
class FixedSizeString
{
public:
	typedef typename _CharT value_type;
	typedef typename size_t size_type;
	typedef typename size_t difference_type;
	typedef typename _CharT* pointer;
	typedef typename const _CharT* const_pointer;
	typedef typename _CharT& reference;
	typedef typename const _CharT& const_reference;

	typedef std::_Array_iterator<_CharT, _Size> iterator;
	typedef std::_Array_const_iterator<_CharT, _Size> const_iterator;
	typedef FixedSizeString<_CharT, _Traits, _Size> _Myt;

private:
	std::array<_CharT, _Size> buf_;
	size_type length_;


public:
	FixedSizeString()
	{
		static_assert(_Size > 0, "FixedSizeString cannot be 0 sized.");

		clear();
	}


	template <class _CharT2, class _Traits2, size_t _Size2>
	FixedSizeString(const FixedSizeString<_CharT2, _Traits2, _Size2>& Other)
	{
		static_assert(_Size > 0, "FixedSizeString cannot be 0 sized.");
		static_assert(_CharT == _CharT2 && _Traits == _Traits2, "FixedSizeString type mismatch.");
		static_assert(_Size2 <= _Size, "FixedSizeString too small.");
		ML_ASSERT(Other.length() < _Size, "Parameter string to copy is too long to fit.")(Other.length(), _Size);

		_Traits::copy(this->buf_.data(), Other.data(), Other.length());
		this->length_ = Other.length();
		this->buf_[this->length_] = 0;
	}


	FixedSizeString(const _CharT* C_String)
	{
		size_t len = _Traits::length(C_String);

		static_assert(_Size > 0, "FixedSizeString cannot be 0 sized.");
		ML_ASSERT(len < _Size, "Parameter string to copy is too long to fit.")(len, _Size);

		_Traits::copy(this->buf_.data(), C_String, len);
		this->length_ = len;
		this->buf_[this->length_] = 0;
	}


	template <class _CharT2, class _Traits2, size_t _Size2>
	_Myt& operator = (const FixedSizeString<_CharT2, _Traits2, _Size2>& Other)
	{
		//static_assert(_CharT == _CharT2 && _Traits == _Traits2, "FixedSizeString type mismatch.");
		//static_assert(_Size2 <= _Size, "FixedSizeString too small.");
		ML_ASSERT(Other.length() < _Size, "Parameter string to copy is too long to fit.")(Other.length(), _Size);

		_Traits::copy(this->buf_.data(), Other.data(), Other.length());
		this->length_ = Other.length();
		this->buf_[this->length_] = 0;

		return *this;
	}


	_Myt& operator = (const _CharT* C_String)
	{
		size_t len = _Traits::length(C_String);

		static_assert(_Size > 0, "FixedSizeString cannot be 0 sized.");
		ML_ASSERT(len < _Size, "Parameter string to copy is too long to fit.")(len, _Size);

		_Traits::copy(this->buf_.data(), C_String, len);
		this->length_ = len;
		this->buf_[this->length_] = 0;

		return *this;
	}


	template <class _CharT2, class _Traits2, size_t _Size2>
	bool operator == (const FixedSizeString<_CharT2, _Traits2, _Size2>& Other) const
	{
		return this->length() == Other.length() && _Traits::compare(this->data(), Other.data(), this->length()) == 0;
	}


	bool operator == (const char* C_String) const
	{
		return this->length() == _Traits::length(C_String) && _Traits::compare(this->data(), C_String, this->length()) == 0;
	}


	template <class _CharT2, class _Traits2, size_t _Size2>
	bool operator != (const FixedSizeString<_CharT2, _Traits2, _Size2>& Other) const
	{
		return !(this->operator==(Other));
	}


	bool operator != (const char* C_String) const
	{
		return !(this->operator==(C_String));
	}


	const _CharT& operator[](size_t Pos)
	{
		ML_ASSERT(Pos < _Size, "Memory bounds allocated for this array exceeded.")(Pos, _Size);
		return this->buf_[Pos];
	}


	// returns size of buffer
	size_t size() const
	{
		return _Size;
	}

	// returns a const c-style string
	const _CharT* data() const 
	{ 
		return this->buf_.data(); 
	}

	
	size_t length() const
	{
		return this->length_;
	}


	// empties the string (resets terminator position to 0)
	void clear()
	{
		this->buf_[0] = 0;
		this->length_ = 0;
	}


	template <class _CharT2, class _Traits2, size_t _Size2>
	void append(const FixedSizeString<_CharT2, _Traits2, _Size2>& Other, size_t Max_Length=((size_t)-1))
	{
		size_t len = Other.length();
		size_t new_length = this->length_;
		if (Max_Length != ((size_t)-1) && len > Max_Length) {
			len = Max_Length;
		}

		new_length += len;

		ML_ASSERT(new_length < _Size, "Parameter string to append is too long to fit.")(new_length, len, _Size);

		_Traits::copy(this->buf_.data() + this->length_, Other.data(), len);
		this->length_ = new_length;
		this->buf_[this->length_] = 0;
	}


	void append(const _CharT* C_String, size_t Max_Length = ((size_t)-1))
	{
		size_t len = 0;
		size_t new_length = this->length_;
		if (Max_Length == ((size_t)-1)) {
			len = _Traits::length(C_String);
		}
		else {
			for (const char* ptr=C_String; *ptr != '\0'; ++ptr)
			{
				if (len == Max_Length)
					break;
				++len;
			}
		}

		new_length += len;

		ML_ASSERT(new_length < _Size, "Parameter string to append is too long to fit.")(new_length, len, _Size);

		_Traits::copy(this->buf_.data() + this->length_, C_String, len);
		this->length_ = new_length;
		this->buf_[this->length_] = 0;
	}


	void append(_CharT Char)
	{
		ML_ASSERT(this->length_ + 1 < _Size, "String is already full.")(this->length_, _Size);

		this->buf_[this->length_] = Char;
		++this->length_;
		this->buf_[this->length_] = 0;
	}


	// format string in printf style
	void format(const _CharT* Format, ...)
	{
		va_list args;
		va_start(args, Format);

		this->length_ = _vsnprintf_s(this->buf_.data(), _Size, _TRUNCATE, Format, args);
		va_end(args);
	}


	// append printf style formatted string
	void append_format(const _CharT* Format, ...)
	{
		va_list args;
		va_start(args, Format);

		int written = 0;
		written = _vsnprintf(this->buf_.data() + this->length_, _Size - this->length_, Format, args);
		ML_ASSERT(written >= 0, "Error occurred in _vstprintf call.")(written, _Size, this->length_, Format);

		if (written < 0) {
			clear();
		} else {
			this->length_ += written;
		}

		va_end(args);
	}


	size_type find(const_pointer Substring, size_type Offset, size_type Length=((size_type)-1), bool Case_Sensitive=true) const
	{
		if (Length == (size_type)-1) {
			Length = _Traits::length(Substring);
		}

		if (Offset > this->length_ || (Offset == this->length_ && Length != 0)) {
			return ((size_type)-1);
		}

		if (Length == 0 && Offset <= this->length_) {
			return Offset;
		}

		size_type matched = 0;
		const_pointer match_begin = this->data();
		const_pointer needle = Substring;
		const_pointer haystack = this->data() + Offset;
		for (size_type i=0; i<this->length_; ++i) 
		{
			value_type needle_char = Case_Sensitive ? *needle : std::toupper(*needle);
			value_type haystack_char = Case_Sensitive ?  *haystack : std::toupper(*haystack);
			if (_Traits::eq(needle_char, haystack_char)) {
				if (matched == 0) {
					match_begin = haystack;
				}
				if (++matched == Length) {
					return (match_begin - this->data());													// return
				}
				++needle;
			}
			else if (matched != 0) {
				// reset counter
				matched = 0;
				needle = Substring;
			}

			++haystack;
		}

		return (size_type)-1;
	}

	int replace(const_pointer Find, const_pointer Replacement, bool Case_Sensitive=true, int Count=-1, size_type Offset=0)
	{
		size_type find_len = _Traits::length(Find);
		size_type repl_len = _Traits::length(Replacement);
		size_type diff_len = 0;
		size_type offset = Offset;
		int replaced = 0;


		if (Offset >= this->length_) {
			return 0;
		}

		if (repl_len == find_len) {
			while ((offset = this->find(Find, offset, find_len, Case_Sensitive)) != (size_type)-1) 
			{
				_Traits::copy(this->buf_.data() + offset, Replacement, repl_len);
				offset += repl_len;

				++replaced;
				if (replaced == Count) {
					return replaced;
				}
			}

			return replaced;
		}


		if (repl_len > find_len) {
			diff_len = repl_len - find_len;
			while (_Size - this->length() > diff_len) 
			{
				offset = this->find(Find, offset, find_len, Case_Sensitive);
				if (offset == (size_type)-1) {
					return replaced;
				}
				else {
					pointer offset_ptr = this->buf_.data() + offset;
					if (this->length() > offset + find_len) {
						_Traits::copy(offset_ptr + repl_len, offset_ptr + find_len, 
							(this->length() - (offset + find_len)));
					}
					_Traits::copy(offset_ptr, Replacement, repl_len);

					offset += repl_len;

					this->length_ += diff_len;
					this->buf_[this->length_] = 0;

					++replaced;
					if (replaced == Count) {
						return replaced;
					}
				}
			}
		}
		else {
			diff_len = find_len - repl_len;
			while ((offset = this->find(Find, offset, find_len, Case_Sensitive)) != (size_type)-1) 
			{
				pointer offset_ptr = this->buf_.data() + offset;
				if (this->length() > offset + find_len) {
					_Traits::copy(offset_ptr + repl_len, offset_ptr + find_len, (this->length() - (offset + find_len)));
				}
				_Traits::copy(offset_ptr, Replacement, repl_len);

				offset += repl_len;

				this->length_ -= diff_len;
				this->buf_[this->length_] = 0;

				++replaced;
				if (replaced == Count) {
					return replaced;
				}
			}
		}

		return replaced;
	}
};

typedef FixedSizeString<char, std::char_traits<char>, 16> string16;
typedef FixedSizeString<char, std::char_traits<char>, 32> string32;
typedef FixedSizeString<char, std::char_traits<char>, 64> string64;
typedef FixedSizeString<char, std::char_traits<char>, 128> string128;
typedef FixedSizeString<char, std::char_traits<char>, 256> string256;
typedef FixedSizeString<char, std::char_traits<char>, 512> string512;
typedef FixedSizeString<char, std::char_traits<char>, 1024>  string1024;
typedef FixedSizeString<char, std::char_traits<char>, 4096>  string4096;
typedef FixedSizeString<char, std::char_traits<char>, 8192>  string8192;
typedef FixedSizeString<char, std::char_traits<char>, 16384>  string16384;

} // namespace ml