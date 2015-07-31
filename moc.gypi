{
  'extension': 'h',
  'outputs': [ 'moc_<(RULE_INPUT_ROOT).cc' ],
  'action':  [
    'moc',
    '-p', '<(RULE_INPUT_DIRNAME)',
    '-o', 'moc_<(RULE_INPUT_ROOT).cc',
	'<(RULE_INPUT_PATH)'
  ]
}
