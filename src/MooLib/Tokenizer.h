#pragma once

#include "FixedString.h"


namespace ml {

// tokenizer that allocates only 1024 bytes on the stack(for string storage), and no heap allocation.
// note: quote escapes can be escaped by backslash
class Tokenizer
{
private:
	const char* m_curr_pos;
	const char* m_end_pos;
	char m_delimiter;
	std::set<char> m_delimiters;
	ml::string16384 m_buf;
	bool m_single_quote;
	bool m_double_quote;


public:
	// constructer copies first token to buffer
	Tokenizer(const char* String, char Delimiter, bool DoubleQuoteEsc=true, bool SingleQuoteEsc=false);
	Tokenizer(const char* String, const std::set<char>& Delimiters, bool DoubleQuoteEsc=true, bool SingleQuoteEsc=false);
	Tokenizer(const char* Start, const char* End, char Delimiter, bool DoubleQuoteEsc=true, bool SingleQuoteEsc=false);
	Tokenizer(const char* Start, const char* End, const std::set<char>& Delimiters, bool DoubleQuoteEsc=true, bool SingleQuoteEsc=false);


	// iterates to next token, returns false if there are no tokens remaining
	bool Next();

	// returns reference of current token
	const ml::string16384& GetRef() const;

	// returns copy of current token
	ml::string16384 GetCopy() const;

	// returns c-style string of current token
	const char* GetPtr() const;

	// returns current position of input string
	const char* GetPos() const;

private:
	ML_NO_COPY(Tokenizer);
	ML_NO_ASSIGN(Tokenizer);
};
} // namespace ml