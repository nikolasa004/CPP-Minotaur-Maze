#include "FogOfWarEffect.h"
#include <iostream>

void FogOfWarEffect::gotMessage()
{
	std::cout<<R"(
                _                                  
              (`  ).                   _           
             (     ).              .:(`  )`.       
)           _(       '`.          :(   .    )      
        .=(`(      .   )     .--  `.  (    ) )      
       ((    (..__.:'-'   .+(   )   ` _`  ) )                 
`.     `(       ) )       (   .  )     (   )  ._   
  )      ` __.:'   )     (   (   ))     `-'.-(`  ) 
)  )  ( )       --'       `- __.'         :(      )) 
.-'  (_.'          .')                    `(    )  ))
                  (_  )                     ` __.:'     
)"<<std::endl;
	std::cout << "You have activated the Fog of War effect! Only 3x3 area around you is visible! Bad luck all day huh?" << std::endl;
}

void FogOfWarEffect::currentMessage()
{
	if (turnsValid == 2)
	{
		std::cout << "Only one turn has passed, Fog of War effect is active two more turns!" << std::endl;
	}
	else if(turnsValid == 1)
	{
		std::cout << "The path is clearing up, Fog of War effect is active one more turns!" << std::endl;
	}
	else
	{
		std::cout << "Fog of War effect is active " << turnsValid << " more turns!" << std::endl;
	}
}

void FogOfWarEffect::lostMessage()
{
	std::cout << "Rub your eyes, the Fog of War effect has ended! You can see the whole maze again!" << std::endl;
}