#!/usr/bin/env ruby
#
require 'nokogiri'
require 'pp'

class Op
    attr_reader :op, :params, :format, :desc
    def initialize(op, params, format, desc)
        @op = op
        @params = params
        @format = format
        @desc = desc
    end

    def to_lex
        @op.gsub(/[-\/]/, "_").upcase
    end

    def to_antlr
         "#{@op.gsub(/[-\/]/, "_")} : #{to_lex} #{@params.join(" ")} ;"
    end
end

class OpTable
    attr_reader :ops
    def initialize
        page = Nokogiri::HTML(open('Dalvik opcodes.html'))

        op_table = page.css("table")

        @ops = op_table[0].css("tr").drop(1).collect{ |tr| [ tr.css("td")[1].text.split("\n").join(" "), tr.css("td")[2].text.split("\n").join(" ") ] }.reject{ |s| s[0].start_with?("unused") }.map{ |a| 
            l = a[0].strip
            ret = [l]
            first_white_space_index = l.index(" ")
            if first_white_space_index
                ret.push( l.slice( 0..(first_white_space_index-1) ) )
                l = l.slice( first_white_space_index..-1 )
            end

            ret = ret + l.split(",").map{ |s| s.strip }
            Op.new( ret[1], ret[2..-1], ret[0], a[1] )
        }
    end
end

optable = OpTable.new

#optable.ops.sort{ |a,b| b.op <=> a.op }.each do |op|
    #puts "        \"#{op.op}\" : { RETURN(#{op.to_lex}); }"
#end

pp optable.ops.map { |op| op.to_antlr }

