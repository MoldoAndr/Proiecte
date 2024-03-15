library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity sonerie is
    Port ( 
            clk : in STD_LOGIC;
            BUTONUL1: in STD_LOGIC;
            BUTONUL2: in std_logic ;
            ROSU : out STD_LOGIC;
            VERDE: out STD_LOGIC;
            GALBEN : out STD_LOGIC
            );
           
end sonerie;


architecture Behavioral of sonerie is

TYPE SEQUENCE IS (sapte_fix, sapte_jumate, opt_fix, opt_jumate, noua_fix);

SIGNAL state : SEQUENCE;
SIGNAL counter : std_logic_vector (1 downto 0);
SIGNAL precedent : std_logic;
SIGNAL stop: std_logic ;
begin
    
    process(clk,BUTONUL1,BUTONUL2)
    begin
        stop <= '0';
        if ( stop = '0' ) then
        
            if (clk'event and clk='1') then
                
                case state is 
                
                when sapte_fix =>
                
                    counter <= "00";
                    if (stop ='1') then 
                        state <= noua_fix;
                        ROSU <= '1';
                        VERDE <= '0';
                        GALBEN  <= '0';                       
                         
                    elsif (BUTONUL1 = '1') then
                        ROSU <='0';
                        VERDE <='1';
                        GALBEN <='0'; 
                        precedent <= '0';
                        state <= sapte_jumate ;
                        
                    elsif (BUTONUL2 = '1') then
                        ROSU <='0';
                        VERDE <='1';
                        GALBEN <='0'; 
                        precedent <= '1';
                        state <= opt_fix ;
                        
                    end if;        
                
                when sapte_jumate =>
                
                    counter <= "01";
                    if (stop ='1') then 
                        state <= noua_fix;
                        ROSU <= '1';
                        
                    elsif (BUTONUL1 = '1') then 
                        precedent<= '0';
                        ROSU <='0';
                        VERDE <='1';
                        GALBEN <='0'; 
                        state <= opt_fix  ;
                        
                    elsif (BUTONUL2 = '1') then
                        ROSU <='0';
                        VERDE <='1';
                        GALBEN <='0'; 
                        precedent <= '1';
                        state <= opt_jumate ;
                        
                    end if;        
                
                
                when opt_fix =>
                 
                    if (precedent = '0') then
                            counter <= "11";
                            stop <= '1';
                            else counter <= "10";
                            
                    if (stop ='1') then 
                        state <= noua_fix;
                        ROSU <= '1';
                        VERDE <= '0';
                        GALBEN  <= '0';
                        
                    elsif (BUTONUL1 = '1') then 
                        ROSU <='0';
                        VERDE <='1';
                        GALBEN <='0'; 
                        state <= opt_jumate ;
                       precedent <= '0';
                       
                    elsif (BUTONUL2 = '1') then
                        state <= noua_fix  ;
                        ROSU <='0';
                        VERDE <='1';
                        GALBEN <='0'; 
                       precedent <= '1';
                       
                    end if;        
                end if;
                
                when opt_jumate =>
                
                if ( counter = "11") then 
                     stop       <= '1';
                     state      <= noua_fix ;
                 end if;
                 
                    if (stop ='1') then 
                        state     <= noua_fix;
                        ROSU     <= '1';
                        VERDE   <= '0';
                        GALBEN <= '0';
                        
                    elsif (BUTONUL1 = '1') then
                        ROSU     <='0';
                        VERDE    <='1';
                        GALBEN <='0'; 
                        state      <= noua_fix ;
                        
                    elsif (BUTONUL2 = '1') then
                        ROSU       <='0';
                        VERDE     <='1';
                        GALBEN  <='0'; 
                        state       <= noua_fix  ;
                    end if;        
       
                when noua_fix =>
                        ROSU        <= '1';
                        VERDE      <='0';
                        GALBEN   <='0';
                        state       <= sapte_fix ;
                        
                when others => 
                        ROSU      <= '1';
                        VERDE    <='0';
                        GALBEN <='0';
                        state      <= sapte_fix;
                
                end case;
                
            end if;
        end if;
    end process;
end Behavioral;
