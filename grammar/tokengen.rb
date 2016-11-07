#!/usr/bin/env ruby 

require 'date'

token_list=%w[ DIR_FIELD DIR_METHOD END_METHOD DIR_CLASS DIR_LOCAL DIR_LOCALS DIR_SOURCE DIR_ANNOTATION END_ANNOTATION DIR_SUPER CLASSNAME ID LEFT_PAREN RIGHT_PAREN LEFT_BRACE RIGHT_BRACE COLON SEMICOLON PRIVATE PUBLIC SLASH VALUE STRING ASSIGN]

File.open("Re2cTokenTypes.txt", "w") do |txt|
    txt.puts "Re2c //Generated at #{DateTime.now} from tokengen.rb"

    File.open("Re2cTokenType.hpp", "w") do |hpp|

        hpp.puts "/*Generated at #{DateTime.now} from tokengen.rb*/" 
        hpp.puts "#ifndef __RE2CTOKENTYPE_HPP__"
        hpp.puts "#define __RE2CTOKENTYPE_HPP__"

        num = 100
        token_list.each do |it|
            txt.puts "#{it}=#{num}"
            hpp.puts "#define #{it} #{num}"
            num += 1
        end

        hpp.puts "#endif /*__RE2CTOKENTYPE_HPP__*/"
    end
end


