/https://code.kx.com/q/learn/tour/tables/
ec1:([]city:`Istanbul`Moscow`London`StPetersburg;country:`Turkey`Russia`UK`Russia;pop:15067724 12615279 9126366 5383890)
ec2:flip`city`country`pop!(`Berlin`Kyiv`Madrid;`Germany`Ukraine`Spain;3748148 3703100 3223334)

select city,pop from ec2 upsert ec1

conts:`Africa`Asia`Australia`Europe`NorthAmerica`SouthAmerica
`:path/to/continents set conts
`:~/q/continents.q set conts
get `:~/q/continents.q