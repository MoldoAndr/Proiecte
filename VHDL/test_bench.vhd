library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity test_bench is
end test_bench;

architecture Behavioral of test_bench is

    component sonerie is
         Port 
                ( 
                clk : in STD_LOGIC;
                BUTONUL1: in STD_LOGIC;
                BUTONUL2: in std_logic ;
                ROSU : out STD_LOGIC;
                VERDE: out STD_LOGIC;
                GALBEN : out STD_LOGIC
                );
      end component;
    
     signal clk : std_logic;
     signal BUTONUL1: std_logic;
     signal BUTONUL2: std_logic;
     signal ROSU : std_logic;
     signal VERDE : std_logic;
     signal GALBEN : std_logic;

begin

      mapare : sonerie 
          port map 
             (
             clk                => clk,
             BUTONUL1  => BUTONUL1,
             BUTONUL2  => BUTONUL2,
             ROSU           => ROSU,
             VERDE         => VERDE,
             GALBEN     => GALBEN
             );
        
        clock_process: process 
           begin 
               
                clk <= '0';
                wait for 10ns;
                clk <= '1';
                wait for 10ns;
            
            end process;
        
        test_process: process
            begin 
            
            BUTONUL1  <= '1';
            BUTONUL2 <= '0';
            wait for 30ns;
            
            BUTONUL1 <= '1';
            BUTONUL2 <= '0';
            wait for 30ns;
            
            BUTONUL1 <= '0';
            BUTONUL2 <='1';
            wait for 30ns;   
        
            end process;
        
end Behavioral;
