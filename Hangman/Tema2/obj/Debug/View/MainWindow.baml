   M S B A M L   `   `   `  ����@  <Tema2, Version=1.0.0.0, Culture=neutral, PublicKeyToken=nullclr-namespace:Tema2Tema2  5   	   /clr-namespace:Tema2.ServicesTema2.Services  5   	       Tema2.View.MainWindow   5   	   \ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    5   	   R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5   	   @d2http://schemas.microsoft.com/expression/blend/2008     5   	   Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     5   	   %localclr-namespace:Tema2     5   	   /local1clr-namespace:Tema2.Services     5   	     � Title$  
MainWindow��5	   	   $	��450��6   $	��800��6)    � DataContext 5
        Tema2.Services.Service  5   
   .��5      � .+�5   
   &   System.Windows.Controls.DataGrid  -   5          Name$ DataGrid��5         AutoGenerateColumns .     
IsReadOnly . $��Right=�5      $��86��6/   $��0,65,626,78q�6:    J� RenderTransformOrigin$ 0.841,0.408&�6O   ��5   A   �� *users+ �� Mode$ TwoWay=� �� UpdateSourceTrigger$ PropertyChanged=� �� SelectedIndex 5      �� *CurrentSelected+$ TwoWay=�$ PropertyChanged=�	   Columns	 5      0  *System.Windows.Controls.DataGridTextColumn  5      ,  &System.Windows.Controls.DataGridColumn
   Header$
 Username��6%      
FontFamily$ Arial)�6�   1  +System.Windows.Controls.DataGridBoundColumn   Binding 67   �� *
Username+$ TwoWay=�$ PropertyChanged=�6�   5      �� 5   
   $��329,83,82.333,143.667q�6Q   ��6   ��  �� ElementName$ DataGrid�� �� Path$ SelectedItem.Image�6r   �� 5   
   $��19,370,677,23q�6   ��6)   �� $ AddUserCommand�.��6S   
New User6]   �� 5   
   $��141,370,546,23q�6   ��6)   �� $ DeleteUserCommand�.��6V   Delete User6c   �� 5   
   $��399,370,266,23q�6   $ 1.532,0.652&�6S   ��6)   �� $ GameStartCommand�.��6x   
New Game6�   �� 5   
   -   5        $��613,370,53,23q�5      .��6;   Exit6A   5      5      