# Material Icon

A collection of icons from [Material Symbols](https://fonts.google.com/icons).

## Usage

Set the App's Icon Provider at the start.
```
App app;
app.AddIconProvider(CreateMaterialIconsProvider());
```

Retrieve icons as needed from the icon provider.

```
const auto icon{app.GetIconProvider()->GetIcon(Icon::ArrowUp)};
```
