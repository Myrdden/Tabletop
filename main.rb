$current = 0

def parseCoin(x)
    x.sub!(/t(?!\.|$)/, 'T,')
    xs = x.split(/\s|\/|\.|,/)
    ys = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1]
    xs.each do |i|
        case i
        when /^[0-9]+A$/
            ys[0] = i.delete("^0-9").to_i
        when /^[0-9]+S$/
            ys[1] = i.delete("^0-9").to_i
        when /^[0-9]+Lb$/
            ys[2] = i.delete("^0-9").to_i
        when /^[0-9]+hLb$/
            ys[3] = i.delete("^0-9").to_i
        when /^[0-9]+T$/
            ys[4] = i.delete("^0-9").to_i
        when /^[0-9]+ht$/
            ys[5] = i.delete("^0-9").to_i
        when /^[0-9]+s$/
            ys[6] = i.delete("^0-9").to_i
        when /^\d+$/
            ys[7] = i.to_i
        when /^[0-9]+h$/
            ys[8] = i.delete("^0-9").to_i
        when /^[0-9]+t$/
            ys[9] = i.delete("^0-9").to_i
        when /^[0-9]+q$/
            ys[10] = i.delete("^0-9").to_i
        when /^[0-9]+p$/
            ys[11] = i.delete("^0-9").to_i
        when /^[0-9]+b$/
            ys[12] = i.delete("^0-9").to_i
        else
            puts "Incorrect formatting: " + i.sub(/T/, 't')
            ys[13] = 0
        end
    end
    return ys
end

class Purse
    @@suffix = ['A ', 'S ', 'Lb ', 'hLb ', 't', 'ht', 's', '/', 'h', 't', 'q', 'p', 'b']
    @@mult = [20736, 3456, 1728, 864, 288, 144, 72, 12, 6, 4, 3, 2, 1]
    attr_accessor :name, :owner, :coins
    def initialize
        @name = ""
        @owner = ""
        @coins = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    end
    def show
        print "\"#{@name}\" contains: "
        i = 0
        xs = ""
        until i == 13 do
            i == 7 && (@coins[4] != 0 || @coins[5] != 0 || @coins[6] != 0) ? xs += ',' : xs
            if @coins[i] != 0
                xs += "#{@coins[i]}#{@@suffix[i]}"
                if i > 7 && i < 13
                    j = i + 1
                    until j == 13 do
                        if @coins[j] != 0
                            xs += '.'
                            j = 12
                        end
                        j += 1
                    end
                end
            end
            i += 1
        end
        puts xs[-1] == '/' ? xs += '-' : xs
    end
    def round(version = 0)
        print "\"#{@name}\" rounds to: "
        t = i = 0
        until i == 13 do
            t += @coins[i] * @@mult[i]
            i += 1
        end
        xs = ""
        if version == 0
            t / 1728 > 0 ? xs += (t / 1728).to_s + 'Lb ' : xs
            t = t % 1728
            t / 288 > 0 ? xs += (t / 288).to_s + 't,' : xs
            t = t % 288
            t / 12 > 0 ? xs += (t / 12).to_s + '/' : xs
            t = t % 12
            t / 2 > 0 ? xs += (t / 2).to_s + 'p' : xs
            t = t % 2
            t == 1 ? xs += ".1b" : xs
        end
        puts xs[-1] == '/' ? xs += '-' : xs
    end
    def add(inp)
        xs = parseCoin(inp)
        if xs[13] == 1
            i = 0
            until i == 13 do
                @coins[i] += xs[i]
                i += 1
            end
            puts "Added."
        else
            puts "Failed. Not Added."
        end
    end
    def rem(inp)
        xs = parseCoin(inp)
        if xs[13] == 1
            i = 0
            until i == 13 do
                @coins[i] -= xs[i]
                i += 1
            end
            puts "Removed."
        else
            puts "Failed. Not Removed."
        end
    end
end

class PC
    @@total = 0
    def initialize(name)
        @name = name
    end
end

test = Purse.new
test.name = "Test"
test.coins[11] = 4
test.coins[8] = 7
test.coins[4] = 2
test.coins[7] = 84
test.coins[6] = 143
test.coins[2] = 4
test.coins[10] = 5
test.coins[12] = 15
test.show
test.round
test.add("4Lb 2t14s,8/7h.5q.4p.15b")
test.show
test.round
test.show
test.round
# puts "Welcome to whatever this is."
# puts "Type \"help\" for commands."
# puts "Type \"exit\", \"quit\", or \"q\" to exit."
# done = false
# until done do
#     print ">> "
#     input = gets.chomp.split(' ')
#     if !input.empty?
#         if input[0] =~ /\b(exit|quit|q)\b/
#             done = !done
#         elsif input[0] =~ /\b(help|h)\b|^\?$/
#             puts "help"
#         else
#             puts "Unrecognized command. Try \"?\" for help."
#         end
#     end
# end