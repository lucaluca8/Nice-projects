   M S B A M L   `   `   `  ����B  >Tema1V2, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null!clr-namespace:Tema1V2Tema1V2  5   	       Tema1V2.MainWindow   5   	   \ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    5   	   R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5   	   @d2http://schemas.microsoft.com/expression/blend/2008     5   	   Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     5   	   'localclr-namespace:Tema1V2     5   	     � Title$  
MainWindow��5   	   $	��450��6   $	��800��6)    � DataContext 5	        Tema1V2.TabCommands  5
   
   .��5      � .+�5   
   o� $	��Top=�6   $��0,0,0,44q�6$   @�5      m� 5      $
��File��6   .@�5      m� $	��New��6    m� Command 6,   ��  �� Path$ AddTabComand�m� 5      $
��Open��6    6-   �� $ OpenTabCommand�m� 5      $
��Save��6    6-   �� $ SaveTabCommand�m� 5      $��
Save as...��6    63   �� $ SaveAsTabCommand�5      m� 5      $��Search��6   .@�5      m� $
��Find��6    6-   �� $ FindCommand�m� 5      $��Replace��6    60   �� $ ReplaceCommand�m� 5      $��Replace all...��6    67   �� $ ReplaceAllCommand�5      m� 5      $
��Help��6   .@�5      m� $��About��6    6.   �� $ AboutCommand�5      5      �� 5   
   $��	0,37,0,44q�6   ��6(   �� *tabs+ �� Mode$ TwoWay=� �� UpdateSourceTrigger$ PropertyChanged=� �� SelectedIndex 5       �� *currentSelected+$ TwoWay=�$ PropertyChanged=���5!      �� 5"      .R�5#      ��  �� Orientation$ 
Horizontal=�6!   .+�5$      �� ��6$   �� *header+$ TwoWay=�$ PropertyChanged=��� 5%      $��X��6!   ��5&   !   �� *DataContext.RemoveTabCommand+ �� RelativeSource �� *FindAncestor+	 �� AncestorType"	 ��5'      5(      
 �� ContentTemplate
 5*      �� 5+      .R�5,      ��  �� 
AcceptsTab .  �� AcceptsReturn . " �� VerticalScrollBarVisibility$
 Auto=�5-      $ �� HorizontalScrollBarVisibility$
 Auto=�6A   ��5,      �� *	content+$ TwoWay=�$ PropertyChanged=�.��5-   f   5.      5/      51      52      53      