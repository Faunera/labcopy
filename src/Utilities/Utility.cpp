module FUtility; 


auto readFile(const std::string& filename) -> std::vector<char>
{
	auto file{ std::ifstream{ filename, std::ios::ate | std::ios::binary } };
	if (!file)
	{
		std::cout << "Failed to open file: " << filename << "\n";
		return {};
	}

	auto fileSize{ static_cast<int>(file.tellg()) };
	auto buffer{ std::vector<char>(toUZ(fileSize)) };

	file.seekg(0);
	file.read(buffer.data(), fileSize);

	file.close();

	return buffer;
}

void writeFile(const std::string& filename, const std::string& content)
{
	auto file{ std::ofstream{filename, std::ios::ate | std::ios::binary | std::ios::app} };
	if (!file)
	{
		std::cout << "Failed to open file for writing: " << filename << "\n";
		return;
	}
	file << content << "\n";
	file.close();
}


void rewriteFile(const std::string& filename, const std::string& content)
{
	auto file{ std::ofstream{filename, std::ios::binary | std::ios::trunc} };
	if (!file)
	{
		std::cout << "Failed to open file for writing: " << filename << "\n";
		return;
	}
	file << content << "\n";
	file.close();
}

/* BYTE STUFF */
std::ostream& operator<<(std::ostream& os, std::byte b)
{
	return os << std::bitset<8>(std::to_integer<uint8>(b));
}


