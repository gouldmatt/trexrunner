library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity lfsr is
    
port(
			clk : in std_logic;
			reset : in std_logic;
			randomNumber : out std_logic_vector(7 downto 0) 
	);
	
end lfsr;

architecture Behavioral of lfsr is
	signal rLfsr : std_logic_vector (7 downto 0):="11001011"; --seed LFSR
	signal feedback : std_logic;
begin
	feedback <= rLfsr(0) xor rLfsr(2) xor rLfsr(3) xor rLfsr(4); --feedback loop
	randomNumber <= rLfsr;
	process (clk)
		begin
		
		  --shift numbers
			if(rising_edge(clk)) then
					rLfsr(1) <= rLfsr(0);
					rLfsr(2) <= rLfsr(1);
					rLfsr(3) <= rLfsr(2);
					rLfsr(4) <= rLfsr(3);
					rLfsr(5) <= rLfsr(4);
					rLfsr(6) <= rLfsr(5);
					rLfsr(7) <= rLfsr(6);
    				rLfsr(0) <= feedback;
			end if;
	end process;
end Behavioral;