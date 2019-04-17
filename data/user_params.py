 
# This file is auto-generated from a Python script that parses a PhysiCell configuration (.xml) file.
#
# Edit at your own risk.
#
import os
from ipywidgets import Label,Text,Checkbox,Button,HBox,VBox,FloatText,IntText,BoundedIntText,BoundedFloatText,Layout,Box
    
class UserTab(object):

    def __init__(self):
        
        micron_units = Label('micron')   # use "option m" (Mac, for micro symbol)

        constWidth = '180px'
        tab_height = '500px'
        stepsize = 10

        #style = {'description_width': '250px'}
        style = {'description_width': '25%'}
        layout = {'width': '400px'}

        name_button_layout={'width':'25%'}
        widget_layout = {'width': '15%'}
        units_button_layout ={'width':'15%'}
        desc_button_layout={'width':'45%'}

        param_name1 = Button(description='random_seed', disabled=True, layout=name_button_layout)
        param_name1.style.button_color = 'lightgreen'

        self.random_seed = IntText(
          value=0,
          step=1,
          style=style, layout=widget_layout)

        param_name2 = Button(description='self_velocity_factor', disabled=True, layout=name_button_layout)
        param_name2.style.button_color = 'tan'

        self.self_velocity_factor = FloatText(
          value=0.5,
          step=0.1,
          style=style, layout=widget_layout)

        param_name3 = Button(description='neigh_velocity_factor', disabled=True, layout=name_button_layout)
        param_name3.style.button_color = 'lightgreen'

        self.neigh_velocity_factor = FloatText(
          value=0.4,
          step=0.1,
          style=style, layout=widget_layout)

        param_name4 = Button(description='previous_bias_factor', disabled=True, layout=name_button_layout)
        param_name4.style.button_color = 'tan'

        self.previous_bias_factor = FloatText(
          value=0.1,
          step=0.01,
          style=style, layout=widget_layout)

        param_name5 = Button(description='noise_factor', disabled=True, layout=name_button_layout)
        param_name5.style.button_color = 'lightgreen'

        self.noise_factor = FloatText(
          value=0.1,
          step=0.01,
          style=style, layout=widget_layout)

        param_name6 = Button(description='motile_cell_persistence_time', disabled=True, layout=name_button_layout)
        param_name6.style.button_color = 'tan'

        self.motile_cell_persistence_time = FloatText(
          value=0.05,
          step=0.01,
          style=style, layout=widget_layout)

        param_name7 = Button(description='motile_cell_migration_speed', disabled=True, layout=name_button_layout)
        param_name7.style.button_color = 'lightgreen'

        self.motile_cell_migration_speed = FloatText(
          value=0.25,
          step=0.01,
          style=style, layout=widget_layout)

        param_name8 = Button(description='pressure_threshold', disabled=True, layout=name_button_layout)
        param_name8.style.button_color = 'tan'

        self.pressure_threshold = FloatText(
          value=0.4,
          step=0.1,
          style=style, layout=widget_layout)

        param_name9 = Button(description='relative_adhesion_strength', disabled=True, layout=name_button_layout)
        param_name9.style.button_color = 'lightgreen'

        self.relative_adhesion_strength = FloatText(
          value=0.01,
          step=0.001,
          style=style, layout=widget_layout)

        param_name10 = Button(description='relative_repulsion_strength', disabled=True, layout=name_button_layout)
        param_name10.style.button_color = 'tan'

        self.relative_repulsion_strength = FloatText(
          value=1.25,
          step=0.1,
          style=style, layout=widget_layout)

        units_button1 = Button(description='', disabled=True, layout=units_button_layout) 
        units_button1.style.button_color = 'lightgreen'
        units_button2 = Button(description='dimless', disabled=True, layout=units_button_layout) 
        units_button2.style.button_color = 'tan'
        units_button3 = Button(description='dimless', disabled=True, layout=units_button_layout) 
        units_button3.style.button_color = 'lightgreen'
        units_button4 = Button(description='dimless', disabled=True, layout=units_button_layout) 
        units_button4.style.button_color = 'tan'
        units_button5 = Button(description='dimless', disabled=True, layout=units_button_layout) 
        units_button5.style.button_color = 'lightgreen'
        units_button6 = Button(description='min', disabled=True, layout=units_button_layout) 
        units_button6.style.button_color = 'tan'
        units_button7 = Button(description='um/min', disabled=True, layout=units_button_layout) 
        units_button7.style.button_color = 'lightgreen'
        units_button8 = Button(description='dimless', disabled=True, layout=units_button_layout) 
        units_button8.style.button_color = 'tan'
        units_button9 = Button(description='dimless', disabled=True, layout=units_button_layout) 
        units_button9.style.button_color = 'lightgreen'
        units_button10 = Button(description='dimless', disabled=True, layout=units_button_layout) 
        units_button10.style.button_color = 'tan'

        desc_button1 = Button(description='', disabled=True, layout=desc_button_layout) 
        desc_button1.style.button_color = 'lightgreen'
        desc_button2 = Button(description='', disabled=True, layout=desc_button_layout) 
        desc_button2.style.button_color = 'tan'
        desc_button3 = Button(description='', disabled=True, layout=desc_button_layout) 
        desc_button3.style.button_color = 'lightgreen'
        desc_button4 = Button(description='', disabled=True, layout=desc_button_layout) 
        desc_button4.style.button_color = 'tan'
        desc_button5 = Button(description='', disabled=True, layout=desc_button_layout) 
        desc_button5.style.button_color = 'lightgreen'
        desc_button6 = Button(description='', disabled=True, layout=desc_button_layout) 
        desc_button6.style.button_color = 'tan'
        desc_button7 = Button(description='', disabled=True, layout=desc_button_layout) 
        desc_button7.style.button_color = 'lightgreen'
        desc_button8 = Button(description='', disabled=True, layout=desc_button_layout) 
        desc_button8.style.button_color = 'tan'
        desc_button9 = Button(description='', disabled=True, layout=desc_button_layout) 
        desc_button9.style.button_color = 'lightgreen'
        desc_button10 = Button(description='', disabled=True, layout=desc_button_layout) 
        desc_button10.style.button_color = 'tan'

        row1 = [param_name1, self.random_seed, units_button1, desc_button1] 
        row2 = [param_name2, self.self_velocity_factor, units_button2, desc_button2] 
        row3 = [param_name3, self.neigh_velocity_factor, units_button3, desc_button3] 
        row4 = [param_name4, self.previous_bias_factor, units_button4, desc_button4] 
        row5 = [param_name5, self.noise_factor, units_button5, desc_button5] 
        row6 = [param_name6, self.motile_cell_persistence_time, units_button6, desc_button6] 
        row7 = [param_name7, self.motile_cell_migration_speed, units_button7, desc_button7] 
        row8 = [param_name8, self.pressure_threshold, units_button8, desc_button8] 
        row9 = [param_name9, self.relative_adhesion_strength, units_button9, desc_button9] 
        row10 = [param_name10, self.relative_repulsion_strength, units_button10, desc_button10] 

        box_layout = Layout(display='flex', flex_flow='row', align_items='stretch', width='100%')
        box1 = Box(children=row1, layout=box_layout)
        box2 = Box(children=row2, layout=box_layout)
        box3 = Box(children=row3, layout=box_layout)
        box4 = Box(children=row4, layout=box_layout)
        box5 = Box(children=row5, layout=box_layout)
        box6 = Box(children=row6, layout=box_layout)
        box7 = Box(children=row7, layout=box_layout)
        box8 = Box(children=row8, layout=box_layout)
        box9 = Box(children=row9, layout=box_layout)
        box10 = Box(children=row10, layout=box_layout)

        self.tab = VBox([
          box1,
          box2,
          box3,
          box4,
          box5,
          box6,
          box7,
          box8,
          box9,
          box10,
        ])

    # Populate the GUI widgets with values from the XML
    def fill_gui(self, xml_root):
        uep = xml_root.find('.//user_parameters')  # find unique entry point into XML
        self.random_seed.value = int(uep.find('.//random_seed').text)
        self.self_velocity_factor.value = float(uep.find('.//self_velocity_factor').text)
        self.neigh_velocity_factor.value = float(uep.find('.//neigh_velocity_factor').text)
        self.previous_bias_factor.value = float(uep.find('.//previous_bias_factor').text)
        self.noise_factor.value = float(uep.find('.//noise_factor').text)
        self.motile_cell_persistence_time.value = float(uep.find('.//motile_cell_persistence_time').text)
        self.motile_cell_migration_speed.value = float(uep.find('.//motile_cell_migration_speed').text)
        self.pressure_threshold.value = float(uep.find('.//pressure_threshold').text)
        self.relative_adhesion_strength.value = float(uep.find('.//relative_adhesion_strength').text)
        self.relative_repulsion_strength.value = float(uep.find('.//relative_repulsion_strength').text)


    # Read values from the GUI widgets to enable editing XML
    def fill_xml(self, xml_root):
        uep = xml_root.find('.//user_parameters')  # find unique entry point into XML 
        uep.find('.//random_seed').text = str(self.random_seed.value)
        uep.find('.//self_velocity_factor').text = str(self.self_velocity_factor.value)
        uep.find('.//neigh_velocity_factor').text = str(self.neigh_velocity_factor.value)
        uep.find('.//previous_bias_factor').text = str(self.previous_bias_factor.value)
        uep.find('.//noise_factor').text = str(self.noise_factor.value)
        uep.find('.//motile_cell_persistence_time').text = str(self.motile_cell_persistence_time.value)
        uep.find('.//motile_cell_migration_speed').text = str(self.motile_cell_migration_speed.value)
        uep.find('.//pressure_threshold').text = str(self.pressure_threshold.value)
        uep.find('.//relative_adhesion_strength').text = str(self.relative_adhesion_strength.value)
        uep.find('.//relative_repulsion_strength').text = str(self.relative_repulsion_strength.value)
