----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 02/13/2020 10:49:48 AM
-- Design Name: 
-- Module Name: lfsr_tb - Behavioral
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity lfsr_tb is
--  Port ( );
end lfsr_tb;

architecture Behavioral of lfsr_tb is
signal clk_tb : std_logic := '1';
signal rst_tb : std_logic;
signal outp_tb : std_logic_vector(3 downto 0) := "0000";
constant clk_period : time := 10ns;

--declare lsfr component
component lfsr is
    port (   clk : in std_logic;
             reset : in std_logic;
             randomNumber : out std_logic_vector(3 downto 0));
end component;

begin

process
begin
--run clock
    clk_tb <= not clk_tb;
    wait for clk_period/2;
end process;    

process
begin
       rst_tb <='1';
       wait for 6 ns;
       
       rst_tb <= '0';
       wait for 200 ns;
end process;

DUT : lfsr port map(clk_tb, rst_tb, outp_tb); --map LFSR block

end Behavioral;
