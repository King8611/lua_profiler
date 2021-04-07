local p = profile()
function h()
	local sum = 0
	for i = 1, 100000 do
		sum = sum + i
	end
	return sum+1
end

local function g()
	local sum = 0
	for i = 1, 1000 do
		sum = sum + h()
	end
	return sum +h()+h()
end

local function f(a)
	g()
	h()
	g()
end

p.start()
f(5)
g()
p.profile_log();
p.stop()
--p.stop()