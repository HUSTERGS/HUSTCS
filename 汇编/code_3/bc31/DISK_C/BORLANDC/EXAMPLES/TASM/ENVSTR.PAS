program EnvTest;
{ program looks for environment strings }

var
  EnvVariable : string;
  EnvValue : string;

function EnvString(s:string) : string; far; external;
{$L ENVSTR.OBJ}
begin
  EnvVariable := 'PROMPT';
  EnvValue := EnvString(EnvVariable);
  if EnvValue='' then EnvValue := '*** not found ***';
  Writeln('Environment Variable:',EnvVariable,'Value:',EnvValue);
end.

