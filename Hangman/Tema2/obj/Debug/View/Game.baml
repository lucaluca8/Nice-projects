   M S B A M L   `   `   `  ����@  <Tema2, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null'clr-namespace:Tema2.View
Tema2.View  5   	   /clr-namespace:Tema2.ServicesTema2.Services  5   	       Tema2.View.Game   5   	   \ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    5   	   R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5   	   @d2http://schemas.microsoft.com/expression/blend/2008     5   	   Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     5   	   *localclr-namespace:Tema2.View     5   	   /local1clr-namespace:Tema2.Services     5   	     � Title$
  Game��5	   	   $	��450��6   $	��800��6#    � DataContext 5
        Tema2.Services.Service  5   
   .��5      � $��0,0,0,0q�6    � ColumnDefinitions 5   
   �� 5      �� 5      $��0* �6   .+�5   
   o� $��0,0,0.333,-0.333q�6   @�5      m� 5      $
��Game��6   .@�5      m� $��SaveGame��6    m� Command 61   ��  �� Path$ SaveGameCommand�m� 5      $��LoadGame��6    61   �� $ LoadGameCommand�m� 5      $��Show statics��6    65   �� $ StatisticsCommand�5      m� 5      $��
Categories��6   .@�5      m� $��All categories��6    67   �� $ LoadAllCommand�6c   m� 5      $��Movies��6    6/   �� $ LoadMoviesCommand�6^   m� 5      $��Programming concepts��6    6=   �� $ LoadProgrammingCommand�6q   m� 5      $��Artists��6    61   �� $ LoadArtistsCommand�6a   m� 5      $��Songs��6    6.   �� $ LoadSongsCommand�6\   5      m� 5       $
��Help��6   .@�5!      m� -   5        $��About��5!      6G   5"      5$      �� 5&   
   $��20(�6   $��10,30,670.333,338.667q�6"   $��52��6A   
Time left:6Y   �� 5'   
   -   5         ��Name$ 
TimerLabel��5'      $��Segoe UI)�6$   $��20(�6:   $	��Top=�6H   $
��Left=�5(      $��109,25,524.333,343.667q�62   6T   �� 5*   
   -   5        $
��Word��5*      $��405,134,0,224q�5+      $��30(�6+   $
��Wrap=�69   $
��Left=�6M   $	��334��6h    J� RenderTransformOrigin$ 0.5,0.5&�6t   ��5*       �� *currentWord+5+   �   �� 5-   
   $��351,221,410.333,167.667q�6   $��Q��62   ��6>   �� $ Qcommand��� 5.   
   $��388,221,373.333,167.667q�6   $��W��62   ��6>   �� $ Wcommand�6b   �� 5/   
   $��425,221,336.333,167.667q�6   $��E��62   ��6>   �� $ Ecommand�6b   �� 50   
   $��462,221,299.333,167.667q�6   $��R��62   ��6>   �� $ Rcommand�6b   �� 51   
   $��499,221,262.333,167.667q�6   $��T��62   ��6>   �� $ Tcommand�6b   �� 52   
   $��536,221,225.333,167.667q�6   $��Y��62   ��6>   �� $ Ycommand�6b   �� 53   
   $��573,221,188.333,167.667q�6   $��U��62   ��6>   �� $ Ucommand�6b   �� 54   
   $��610,221,151.333,167.667q�6   $��I��62   ��6>   �� $ Icommand�6b   �� 55   
   $��647,221,114.333,167.667q�6   $��O��62   ��6>   �� $ Ocommand�6b   �� 56   
   $��331,258,430.333,130.667q�6   $��P��62   ��6>   �� $ Pcommand�6b   �� 57   
   $��368,258,393.333,130.667q�6   $��A��62   ��6>   �� $ Acommand�6b   �� 58   
   $��405,258,356.333,130.667q�6   $��S��62   ��6>   �� $ Scommand�6b   �� 59   
   $��442,259,319.333,130.667q�6   $��D��62   ��6>   �� $ Dcommand�6b   �� 5:   
   $��479,259,282.333,130.667q�6   $��F��62   ��6>   �� $ Fcommand�6b   �� 5;   
   $��516,259,245.333,130.667q�6   $��G��62   ��6>   �� $ Gcommand�6b   �� 5<   
   $��553,258,208.333,130.667q�6   $��H��62   ��6>   �� $ Hcommand�6b   �� 5=   
   $��590,259,171.333,130.667q�6   $��J��62   ��6>   �� $ Jcommand�6b   �� 5>   
   $��627,259,134.333,130.667q�6   $��K��62   ��6>   �� $ Kcommand�6b   �� 5?   
   $��664,259,97.333,130.667q�6   $��L��61   ��6=   �� $ Lcommand�6a   �� 5@   
   $��388,295,373.333,94.667q�6   $��Z��61   ��6=   �� $ Zcommand�6a   �� 5A   
   $��425,295,336.333,94.667q�6   $��X��61   ��6=   �� $ Xcommand�6a   �� 5B   
   $��462,295,299.333,94.667q�6   $��C��61   ��6=   �� $ Ccommand�6a   �� 5C   
   $��499,295,262.333,94.667q�6   $��V��61   ��6=   �� $ Vcommand�6a   �� 5D   
   $��536,295,225.333,94.667q�6   $��B��61   ��6=   �� $ Bcommand�6a   �� 5E   
   $��573,295,188.333,94.667q�6   $��N��61   ��6=   �� $ Ncommand�6a   �� 5F   
   $��610,295,151.333,94.667q�6   $��M��61   ��6=   �� $ Mcommand�6a   �� 5H   
   -   5        $��651,388,53,0q�5H      .��6:   EXIT6@   �� 5I   
   $��Center=�6   $��Center=�5J      $��20(�6+   $��58,364,660.333,9.667q�69   Lifes:6_   �� 5K   
   $��122,368,639,15q�6   $��24(�6,   ��6:   �� *lives+6S   �� 5L   
   $��19,82,542,94q�6   ��6&   �� *currentHangmanImage+6P   �� 5M   
   -   5         ��Name$ Username��5M      $��524,10,18,366q�6&   $��20(�6=   5N      �� 5O   
   -   5        $��315,381,356,0q�5O      ��6<   �� $ StartCommand�.��6b   Start6i   �� 5P   
   $��Score:��6   $��20(�6"   $��221,80,488,295q�61   $ -1.177,-1.701&�6I   6q   �� 5Q   
   $��20(�6+   $��279,82,385,295q�6:   $ -2.18,-2.448&�6R   ��6   �� *score+6y   5R      5S      