#include "pch.h"
#include "Tokenizer.h"


namespace ml {
	

// ---------------------------------------------------------------------------------------------------------------------
// class Tokenizer implementation
// ---------------------------------------------------------------------------------------------------------------------
Tokenizer::Tokenizer(const char* String, char Delimiter, bool DoubleQuoteEsc/*=true*/, bool SingleQuoteEsc/*=false*/)
	: m_curr_pos(String), m_double_quote(DoubleQuoteEsc), m_single_quote(SingleQuoteEsc), m_delimiter(Delimiter)
{
	m_end_pos = strchr(m_curr_pos, '\0');
	this->Next();
}


Tokenizer::Tokenizer(const char* String, const std::set<char>& Delimiters, bool DoubleQuoteEsc/*=true*/, bool SingleQuoteEsc/*=false*/)
	: m_curr_pos(String), m_delimiters(Delimiters), m_double_quote(DoubleQuoteEsc), m_single_quote(SingleQuoteEsc)
{
	m_end_pos = strchr(m_curr_pos, '\0');
	this->Next();
}


Tokenizer::Tokenizer(const char* Start, const char* End, char Delimiter, bool DoubleQuoteEsc/*=true*/, bool SingleQuoteEsc/*=false*/)
	: m_curr_pos(Start), m_end_pos(End), m_double_quote(DoubleQuoteEsc), m_single_quote(SingleQuoteEsc), m_delimiter(Delimiter)
{
	this->Next();
}


Tokenizer::Tokenizer(const char* Start, const char* End, const std::set<char>& Delimiters, bool DoubleQuoteEsc/*=true*/, bool SingleQuoteEsc/*=false*/)
	: m_curr_pos(Start), m_end_pos(End), m_delimiters(Delimiters), m_double_quote(DoubleQuoteEsc), m_single_quote(SingleQuoteEsc)
{
	this->Next();
}


bool Tokenizer::Next()
{
	// check if has reached end of string
	if (m_curr_pos == m_end_pos) {
		return false;
	}

	std::function<bool (const char)> is_delimiter;

	if (m_delimiters.empty()) {
		is_delimiter = [&] (const char delimiter) { 
			return m_delimiter == delimiter;
		};
	}
	else {
		is_delimiter = [&] (const char delimiter) { 
			return m_delimiters.find(delimiter) != m_delimiters.end();
		};
	}

	bool dblquote=false;
	bool snglquote=false;
	const char* start = m_curr_pos;
	while (m_curr_pos != m_end_pos)
	{
		// check for delimiter
		if (!dblquote && !snglquote && is_delimiter(*m_curr_pos)) {
			break;
		}

		// check for unescaped double quote tag
		if (m_double_quote && *m_curr_pos == '"' && (m_curr_pos == start || *(m_curr_pos - 1) != '\\')) {
			dblquote = !dblquote;
		}

		// check for unescaped single quote tag
		if (m_single_quote && *m_curr_pos == '\'' && (m_curr_pos == start || *(m_curr_pos - 1) != '\\')) {
			snglquote = !snglquote;
		}
		++m_curr_pos;
	}

	m_buf.clear();
	m_buf.append(start, m_curr_pos - start);

	// remove double quotes & backslashes from buffer
	if (m_double_quote) {
		size_t pos = 0;
		while ((pos = m_buf.find("\"", pos)) != (size_t)-1) {
			if (pos == 0) {
				// backslash can't exist if quote at beginning, replace quote
				m_buf.replace("\"", "", true, 1, pos);
			}
			else if (m_buf[pos - 1] == '\\') {
				// backslash exists, leave quote
				m_buf.replace("\\", "", true, 1, pos - 1);
			}
			else {
				// no backslash, replace quote
				m_buf.replace("\"", "", true, 1, pos);
			}
		}
	}

	// remove single quotes from buffer
	if (m_single_quote) {
		size_t pos = 0;
		while ((pos = m_buf.find("'", pos)) != (size_t)-1) {
			if (pos == 0) {
				// backslash can't exist if quote at beginning, replace quote
				m_buf.replace("'", "", true, 1, pos);
			}
			else if (m_buf[pos - 1] == '\\') {
				// backslash exists, leave quote
				m_buf.replace("\\", "", true, 1, pos - 1);
			}
			else {
				// no backslash, replace quote
				m_buf.replace("'", "", true, 1, pos);
			}
		}
	}

	// increment passed the delimiters if not at end
	while (m_curr_pos != m_end_pos && is_delimiter(*m_curr_pos)) {
		++m_curr_pos;
	}

	return true;
}


const ml::string16384& Tokenizer::GetRef() const
{
	return m_buf;
}


ml::string16384 Tokenizer::GetCopy() const
{
	return m_buf;
}


const char* Tokenizer::GetPtr() const
{
	return m_buf.data();
}


const char* Tokenizer::GetPos() const
{
	return m_curr_pos;
}
} // namespace ml