print("hello")
local p = profile()
p.start()

local l = 1
local function g(a)
	if a <= 0 then
		return 0
	end

	return g(a-2)+l
end

local function f(a)
	if a == 0 then
		return 1
	end
	local x = g(a) - l
	return f(a-1)*x
end

local a = f(10)

--local p = profile()
--print("hello")

--print(p)


--p.start()

--foo(20)